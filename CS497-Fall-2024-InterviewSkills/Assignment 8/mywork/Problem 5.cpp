#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std;

enum class VideoQuality {
    P240, P360, P480, P720, P1080, P4K
};

struct VideoMetadata {
    string videoId;
    string uploaderId;
    string title;
    string description;
    vector<string> tags;
    string category;
    chrono::system_clock::time_point uploadTime;
    uint64_t viewCount = 0;
    uint64_t likeCount = 0;
    uint64_t dislikeCount = 0;
};

struct TranscodedVideoInfo {
    VideoQuality quality;
    string url; // CDN URL to access this transcoded variant
};

struct VideoRecord {
    VideoMetadata metadata;
    vector<TranscodedVideoInfo> transcodedVariants;
};

struct UserProfile {
    string userId;
    string userName;
    string email;
    vector<string> subscribedChannels;
    vector<string> watchHistory; // list of videoIds
};

struct Comment {
    string commentId;
    string videoId;
    string userId;
    string text;
    chrono::system_clock::time_point timestamp;
    uint64_t likeCount = 0;
};

class IUserService {
public:
    virtual ~IUserService() = default;
    virtual UserProfile getUser(const string& userId) = 0;
    virtual void updateUser(const UserProfile& user) = 0;
    virtual void subscribeChannel(const string& userId, const string& channelId) = 0;
    virtual vector<string> getUserSubscriptions(const string& userId) = 0;
};

class IVideoMetadataService {
public:
    virtual ~IVideoMetadataService() = default;
    virtual string uploadVideoMetadata(const VideoMetadata& metadata) = 0;
    virtual VideoMetadata getVideoMetadata(const string& videoId) = 0;
    virtual void updateVideoMetadata(const VideoMetadata& metadata) = 0;
    virtual void incrementViewCount(const string& videoId) = 0;
    virtual vector<VideoMetadata> searchVideos(const string& query, size_t limit, size_t offset) = 0;
};

class IVideoTranscodingService {
public:
    virtual ~IVideoTranscodingService() = default;
    virtual void requestTranscode(const string& videoId, const string& filePath) = 0;
    virtual vector<TranscodedVideoInfo> getTranscodedVariants(const string& videoId) = 0;
};

class IVideoDeliveryService {
public:
    virtual ~IVideoDeliveryService() = default;
    virtual string getStreamingManifest(const string& videoId) = 0;
};

class IRecommendationService {
public:
    virtual ~IRecommendationService() = default;
    virtual vector<VideoMetadata> getRecommendedVideos(const string& userId, size_t limit) = 0;
    virtual vector<VideoMetadata> getTrendingVideos(size_t limit) = 0;
};

class ICommentService {
public:
    virtual ~ICommentService() = default;
    virtual string addComment(const string& videoId, const string& userId, const string& text) = 0;
    virtual vector<Comment> getCommentsForVideo(const string& videoId, size_t limit, size_t offset) = 0;
};

class UserService final : public IUserService {
    unordered_map<string, UserProfile> userStorage;
public:
    UserProfile getUser(const string& userId) override {
        return userStorage[userId];
    }

    void updateUser(const UserProfile& user) override {
        userStorage[user.userId] = user;
    }

    void subscribeChannel(const string& userId, const string& channelId) override {
        userStorage[userId].subscribedChannels.push_back(channelId);
    }

    vector<string> getUserSubscriptions(const string& userId) override {
        return userStorage[userId].subscribedChannels;
    }
};

class VideoMetadataService final : public IVideoMetadataService {
    unordered_map<string, VideoMetadata> videoStorage;
public:
    string uploadVideoMetadata(const VideoMetadata& metadata) override {
        videoStorage[metadata.videoId] = metadata;
        return metadata.videoId;
    }

    VideoMetadata getVideoMetadata(const string& videoId) override {
        return videoStorage[videoId];
    }

    void updateVideoMetadata(const VideoMetadata& metadata) override {
        videoStorage[metadata.videoId] = metadata;
    }

    void incrementViewCount(const string& videoId) override {
        videoStorage[videoId].viewCount++;
    }

    vector<VideoMetadata> searchVideos(const string& query, const size_t limit, const size_t offset) override {
        // Naive: just scans all videos for matching title or tags
        vector<VideoMetadata> results;
        for (auto &kv : videoStorage) {
            const auto &v = kv.second;
            if (v.title.find(query) != string::npos) {
                results.push_back(v);
            } else {
                for (auto &tag : v.tags) {
                    if (tag.find(query) != string::npos) {
                        results.push_back(v);
                        break;
                    }
                }
            }
        }
        // Sort by relevance or popularity in a real system
        // Apply offset and limit
        const size_t end = min(offset + limit, results.size());
        if (offset < results.size()) {
            const auto diff_offset = static_cast<std::vector<VideoMetadata>::difference_type>(offset);
            const auto diff_end = static_cast<std::vector<VideoMetadata>::difference_type>(end);
            return {results.begin() + diff_offset, results.begin() + diff_end};
        }
        return {};
    }
};

class DummyTranscodingService final : public IVideoTranscodingService {
    // For simplicity, pretend each video gets instantly transcoded into multiple qualities
    unordered_map<string, vector<TranscodedVideoInfo>> transcodingResults;
public:
    void requestTranscode(const string& videoId, const string& filePath) override {
        transcodingResults[videoId] = {
            {VideoQuality::P360, "https://cdn.example.com/" + videoId + "/360p.mp4"},
            {VideoQuality::P720, "https://cdn.example.com/" + videoId + "/720p.mp4"},
            {VideoQuality::P1080, "https://cdn.example.com/" + videoId + "/1080p.mp4"}
        };
    }

    vector<TranscodedVideoInfo> getTranscodedVariants(const string& videoId) override {
        return transcodingResults[videoId];
    }
};

class DummyVideoDeliveryService final : public IVideoDeliveryService {
public:
    string getStreamingManifest(const string& videoId) override {
        // In a real system, generate a DASH or HLS manifest referencing multiple bitrate streams
        return "https://cdn.example.com/" + videoId + "/manifest.mpd";
    }
};

class DummyRecommendationService final : public IRecommendationService {
    IVideoMetadataService* videoMetadataService;
public:
    explicit DummyRecommendationService(IVideoMetadataService* vms) : videoMetadataService(vms) {}

    vector<VideoMetadata> getRecommendedVideos(const string& userId, const size_t limit) override {
        // Dummy: return some random videos or top viewed
        // In reality, use ML models and user’s watch history
        return videoMetadataService->searchVideos("", limit, 0);
    }

    vector<VideoMetadata> getTrendingVideos(const size_t limit) override {
        // Dummy: search with no query and pick top viewed videos
        auto allVideos = videoMetadataService->searchVideos("", 1000, 0);
        sort(allVideos.begin(), allVideos.end(), [](auto &a, auto &b) {
            return a.viewCount > b.viewCount;
        });
        if (allVideos.size() > limit) allVideos.resize(limit);
        return allVideos;
    }
};

class CommentService : public ICommentService {
    unordered_map<string, vector<Comment>> commentsByVideo;
public:
    string addComment(const string& videoId, const string& userId, const string& text) override {
        string commentId = videoId + "_c" + to_string(commentsByVideo[videoId].size() + 1);
        Comment c{commentId, videoId, userId, text, chrono::system_clock::now(), 0};
        commentsByVideo[videoId].push_back(c);
        return commentId;
    }

    vector<Comment> getCommentsForVideo(const string& videoId, const size_t limit, const size_t offset) override {
        auto &comments = commentsByVideo[videoId];
        const size_t end = min(offset + limit, comments.size());
        if (offset < comments.size()) {
            const auto diff_offset = static_cast<std::ptrdiff_t>(offset);
            const auto diff_end = static_cast<std::ptrdiff_t>(end);

            return {comments.begin() + diff_offset, comments.begin() + diff_end};

        }
        return {};
    }
};

int main() {
    UserService userService;
    VideoMetadataService videoMetadataService;
    DummyTranscodingService transcodingService;
    DummyVideoDeliveryService videoDeliveryService;
    DummyRecommendationService recommendationService(&videoMetadataService);
    CommentService commentService;

    // Simulate a user uploading a video
    UserProfile uploader{"user1", "Alice", "alice@example.com", {}, {}};
    userService.updateUser(uploader);

    VideoMetadata meta{
        "video1", "user1", "My First Video", "A cool video about C++", {"c++", "tutorial"}, "Education",
        chrono::system_clock::now()
    };

    videoMetadataService.uploadVideoMetadata(meta);
    // Request transcoding
    transcodingService.requestTranscode("video1", "/path/to/video1.mp4");

    // Simulate a view
    videoMetadataService.incrementViewCount("video1");

    // Get a streaming manifest for the video
    string manifest = videoDeliveryService.getStreamingManifest("video1");
    cout << "Manifest URL: " << manifest << endl;

    // Add a comment
    commentService.addComment("video1", "user1", "Great video!");

    // Get recommendations
    auto recs = recommendationService.getRecommendedVideos("user1", 5);
    cout << "Recommended videos:" << endl;
    for (auto &v : recs) {
        cout << " - " << v.title << " (views: " << v.viewCount << ")" << endl;
    }

    return 0;
}