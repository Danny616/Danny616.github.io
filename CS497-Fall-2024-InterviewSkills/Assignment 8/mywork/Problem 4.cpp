#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std;

// Represents privacy settings for a post
enum class PrivacySetting {
    PUBLIC,
    FOLLOWERS_ONLY,
    PRIVATE_MENTIONED
};

struct UserProfile {
    string userId;       // Unique user ID
    string userName;     // Display name
    string handle;       // @handle
    string bio;
    string avatarUrl;
    unordered_set<string> followers;
    unordered_set<string> following;
    // Additional settings, e.g. language, privacy defaults, etc.
};

struct Post {
    std::string postId;
    std::string authorId;
    std::string content;
    PrivacySetting privacy = PrivacySetting::PUBLIC; // Default initialization
    std::chrono::system_clock::time_point timestamp;
    std::vector<std::string> mentions;
    std::vector<std::string> hashtags;
    std::vector<std::string> replies;
    uint64_t favoriteCount = 0;
    uint64_t repostCount = 0;
};

struct DirectMessage {
    string messageId;
    string senderId;
    string receiverId;
    string text;
    chrono::system_clock::time_point sentTime;
    bool read{};
};

class IUserService {
public:
    virtual ~IUserService() = default;
    virtual UserProfile getUser(const string& userId) = 0;
    virtual void updateUser(const UserProfile& user) = 0;
    virtual bool followUser(const string& followerId, const string& followeeId) = 0;
    virtual bool unfollowUser(const string& followerId, const string& followeeId) = 0;
    virtual bool isFollowing(const string& userId, const string& targetUserId) = 0;
};

class IPostService {
public:
    virtual ~IPostService() = default;
    virtual string createPost(const string& authorId,
                                   const string& content,
                                   PrivacySetting privacy,
                                   const vector<string>& mentions,
                                   const vector<string>& hashtags) = 0;
    virtual Post getPost(const string& postId) = 0;
    virtual void replyToPost(const string& postId, const string& replyPostId) = 0;
    virtual void favoritePost(const string& postId, const string& userId) = 0;
    virtual vector<Post> getPostsByUser(const string& userId, size_t limit, size_t offset) = 0;
    virtual void incrementRepostCount(const string& postId) = 0;
};

class IFeedService {
public:
    virtual ~IFeedService() = default;
    // Fetches a personalized feed based on follows, relevancy, etc.
    virtual vector<Post> getFeedForUser(const string& userId, size_t limit, size_t offset) = 0;
};

class ITrendingService {
public:
    virtual ~ITrendingService() = default;
    virtual vector<string> getTrendingHashtags(size_t limit) = 0;
};

class IMessageService {
public:
    virtual ~IMessageService() = default;
    virtual string sendMessage(const string& senderId, const string& receiverId, const string& text) = 0;
    virtual vector<DirectMessage> getMessagesBetween(const string& userId1, const string& userId2, size_t limit, size_t offset) = 0;
};

class IPrivacyService {
public:
    virtual ~IPrivacyService() = default;
    virtual bool canViewPost(const string& viewerId, const Post& post) = 0;
};

class UserService final : public IUserService {
    // Assume distributed KV store or graph database backend
    unordered_map<string, UserProfile> userStorage;
public:
    UserProfile getUser(const string& userId) override {
        // In real implementation, fetch from distributed cache or DB
        return userStorage[userId];
    }

    void updateUser(const UserProfile& user) override {
        userStorage[user.userId] = user;
    }

    bool followUser(const string& followerId, const string& followeeId) override {
        auto& follower = userStorage[followerId];
        auto& followee = userStorage[followeeId];
        if (followee.followers.find(followerId) == followee.followers.end()) {
            followee.followers.insert(followerId);
            follower.following.insert(followeeId);
            return true;
        }
        return false;
    }

    bool unfollowUser(const string& followerId, const string& followeeId) override {
        auto& follower = userStorage[followerId];
        auto& followee = userStorage[followeeId];
        if (followee.followers.erase(followerId)) {
            follower.following.erase(followeeId);
            return true;
        }
        return false;
    }

    bool isFollowing(const string& userId, const string& targetUserId) override {
        auto user = getUser(userId);
        return user.following.find(targetUserId) != user.following.end();
    }
};

class PostService final : public IPostService {
    unordered_map<string, Post> postStorage;
public:
    string createPost(const string& authorId,
                           const string& content,
                           const PrivacySetting privacy,
                           const vector<string>& mentions,
                           const vector<string>& hashtags) override {
        string postId = "post_" + to_string(postStorage.size() + 1);
        const Post p{postId, authorId, content, privacy, chrono::system_clock::now(), mentions, hashtags, {}, 0, 0};
        postStorage[postId] = p;
        return postId;
    }

    Post getPost(const string& postId) override {
        return postStorage[postId];
    }

    void replyToPost(const string& postId, const string& replyPostId) override {
        postStorage[postId].replies.push_back(replyPostId);
    }

    void favoritePost(const string& postId, const string& userId) override {
        // In a real system: possibly store who favorited to prevent double counting
        postStorage[postId].favoriteCount++;
    }

    vector<Post> getPostsByUser(const string& userId, size_t limit, size_t offset) override {
        // In a real system: would query by user index, sorted by time
        // Here, just a naive scan:
        vector<Post> result;
        for (auto& kv : postStorage) {
            if (kv.second.authorId == userId) {
                result.push_back(kv.second);
            }
        }
        // Sorting, offset, limit would happen here
        return result;
    }

    void incrementRepostCount(const string& postId) override {
        postStorage[postId].repostCount++;
    }
};

class FeedService final : public IFeedService {
    IUserService* userService;
    IPostService* postService;
public:
    FeedService(IUserService* us, IPostService* ps) : userService(us), postService(ps) {}
    vector<Post> getFeedForUser(const string& userId, const size_t limit, size_t offset) override {
        // In a real system:
        // 1. Get followee list
        // 2. Fetch recent posts from followees
        // 3. Sort by relevancy (ML ranking), apply filters, paginate
        const auto user = userService->getUser(userId);
        vector<Post> feed;
        for (auto& followee : user.following) {
            auto posts = postService->getPostsByUser(followee, limit, 0);
            feed.insert(feed.end(), posts.begin(), posts.end());
        }
        // Sort and apply offset/limit logic
        return feed;
    }
};

class TrendingService final : public ITrendingService {
public:
    vector<string> getTrendingHashtags(size_t limit) override {
        // Real implementation would query a trending index
        return {"#worldcup", "#music", "#tech"};
    }
};

class MessageService final : public IMessageService {
    unordered_map<string, DirectMessage> messageStorage;
public:
    string sendMessage(const string& senderId, const string& receiverId, const string& text) override {
        string messageId = "msg_" + to_string(messageStorage.size() + 1);
        const DirectMessage dm{messageId, senderId, receiverId, text, chrono::system_clock::now(), false};
        messageStorage[messageId] = dm;
        return messageId;
    }

    vector<DirectMessage> getMessagesBetween(const string& userId1, const string& userId2, size_t limit, size_t offset) override {
        // Naive implementation:
        vector<DirectMessage> result;
        for (auto& kv : messageStorage) {
            const auto& m = kv.second;
            if ((m.senderId == userId1 && m.receiverId == userId2) ||
                (m.senderId == userId2 && m.receiverId == userId1)) {
                result.push_back(m);
            }
        }
        // Sort by time and apply pagination in a real system
        return result;
    }
};

class PrivacyService final : public IPrivacyService {
    IUserService* userService;
public:
    explicit PrivacyService(IUserService* us) : userService(us) {}
    bool canViewPost(const string& viewerId, const Post& post) override {
        if (post.privacy == PrivacySetting::PUBLIC) {
            return true;
        }
        if (post.privacy == PrivacySetting::FOLLOWERS_ONLY) {
            return userService->isFollowing(viewerId, post.authorId) || viewerId == post.authorId;
        }
        if (post.privacy == PrivacySetting::PRIVATE_MENTIONED) {
            // Viewer must be mentioned or the author
            if (viewerId == post.authorId) {
                return true;
            }
            return any_of(post.mentions.begin(), post.mentions.end(),
                               [&](const std::string &mention) {
                                   return mention == viewerId;
                               });
        }
        return false;
    }
};

int main() {
    UserService userService;
    PostService postService;
    FeedService feedService(&userService, &postService);
    PrivacyService privacyService(&userService);

    // Create some users
    UserProfile alice{"1", "Alice Wonderland", "@alice", "Bio of Alice", "https://example.com/alice.jpg"};
    UserProfile bob{"2", "Bob Builder", "@bob", "Bio of Bob", "https://example.com/bob.jpg"};
    userService.updateUser(alice);
    userService.updateUser(bob);

    // Alice follows Bob
    userService.followUser("1", "2");

    // Bob creates a public post
    string postId = postService.createPost("2", "Hello world!", PrivacySetting::PUBLIC, {}, {});
    Post bobPost = postService.getPost(postId);

    // Check if Alice can view Bob's post
    bool canView = privacyService.canViewPost("1", bobPost);
    cout << "Can Alice view Bob's post? " << (canView ? "Yes" : "No") << endl;

    // Fetch Alice's feed
    auto feed = feedService.getFeedForUser("1", 10, 0);
    cout << "Alice's feed has " << feed.size() << " posts." << endl;

    return 0;
}