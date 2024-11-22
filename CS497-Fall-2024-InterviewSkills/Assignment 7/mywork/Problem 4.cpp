#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>

using namespace std;

struct Location {
    double latitude;
    double longitude;
    explicit Location(const double lat = 0.0, const double lon = 0.0) : latitude(lat), longitude(lon) {}

    double distanceTo(const Location& other) const {
        // Simplified distance calculation (Euclidean distance)
        const double dx = latitude - other.latitude;
        const double dy = longitude - other.longitude;
        return sqrt(dx * dx + dy * dy);
    }
};

class User {
public:
    string userId;
    string name;
    vector<string> rideHistory;

    User(string  id, string  n) : userId(move(id)), name(move(n)) {}

    void addRideToHistory(const string& rideId) {
        rideHistory.push_back(rideId);
    }

    void displayRideHistory() const {
        cout << "Ride History for " << name << ":\n";
        for (const auto& rideId : rideHistory) {
            cout << "- Ride ID: " << rideId << "\n";
        }
    }
};

class Driver {
public:
    string driverId;
    string name;
    Location currentLocation;
    bool available;
    double rating;
    int totalRatings;
    int totalTrips;
    string vehicleMake;
    string vehicleModel;
    string licensePlate;
    string status; // "Online", "Offline", "OnTrip"

    Driver(string  id, string  n, const Location& loc,
           string  vMake, string  vModel, string  plate)
        : driverId(move(id)), name(move(n)), currentLocation(loc), available(true), rating(5.0),
          totalRatings(0), totalTrips(0), vehicleMake(move(vMake)), vehicleModel(move(vModel)),
          licensePlate(move(plate)), status("Online") {}

    void updateLocation(const Location& loc) {
        currentLocation = loc;
    }

    void setAvailability(const bool avail) {
        available = avail;
        status = avail ? "Online" : "Offline";
    }

    void startTrip() {
        available = false;
        status = "OnTrip";
    }

    void endTrip() {
        available = true;
        status = "Online";
        totalTrips++;
    }

    void updateRating(const double newRating) {
        // Update average rating
        rating = (rating * totalRatings + newRating) / (totalRatings + 1);
        totalRatings++;
    }

    void displayInfo() const {
        cout << "Driver ID: " << driverId << ", Name: " << name
                  << ", Vehicle: " << vehicleMake << " " << vehicleModel
                  << ", License Plate: " << licensePlate
                  << ", Rating: " << fixed << setprecision(1) << rating << "\n";
    }
};

class Ride {
public:
    string rideId;
    string userId;
    string driverId;
    Location pickupLocation;
    Location dropoffLocation;
    double price;
    string status; // "Requested", "Accepted", "Cancelled", "Completed"

    Ride(string  id, string  uId, string  dId,
         const Location& pickup, const Location& dropoff, double p)
        : rideId(move(id)), userId(move(uId)), driverId(move(dId)), pickupLocation(pickup),
          dropoffLocation(dropoff), price(p), status("Requested") {}

    void updateStatus(const string& newStatus) {
        status = newStatus;
    }
};

class PaymentProcessor {
public:
    static bool processPayment(const string& userId, const double amount) {
        cout << "Processing payment of $" << amount << " for user " << userId << "\n";
        return true;
    }

    static bool processRefund(const string& userId, const double amount) {
        cout << "Processing refund of $" << amount << " for user " << userId << "\n";
        return true;
    }
};

class RideService {
    map<string, User*> users;
    map<string, Driver*> drivers;
    map<string, Ride*> rides;
    PaymentProcessor paymentProcessor;

public:
    void addUser(User* user) {
        users[user->userId] = user;
    }

    void addDriver(Driver* driver) {
        drivers[driver->driverId] = driver;
    }

    vector<pair<Driver*, double>> findNearbyDrivers(const Location& location, const double radius) const {
        vector<pair<Driver*, double>> nearbyDrivers;
        for (auto& pair : drivers) {
            Driver* driver = pair.second;
            if (driver->available && driver->status == "Online") {
                double distance = driver->currentLocation.distanceTo(location);
                if (distance <= radius) {
                    nearbyDrivers.emplace_back(driver, distance);
                }
            }
        }
        return nearbyDrivers;
    }

    void displayAvailableCabs(const Location& userLocation) const {
        const auto driversList = findNearbyDrivers(userLocation, 10.0);
        if (driversList.empty()) {
            cout << "No drivers available nearby.\n";
            return;
        }
        cout << "Available cabs:\n";
        for (const auto& pair : driversList) {
            const Driver* driver = pair.first;
            const double distance = pair.second;
            const double price = calculatePrice(distance);
            const double eta = calculateETA(distance);
            cout << "- ";
            driver->displayInfo();
            cout << "  Price: $" << fixed << setprecision(2) << price
                      << ", ETA: " << fixed << setprecision(1) << eta << " mins\n";
        }
    }

    static double calculatePrice(const double distance) {
        // Simplified price calculation
        return 5.0 + distance * 1.5; // Base fare + per km rate
    }

    static double calculateETA(const double distance) {
        // Simplified ETA calculation (assuming average speed of 30 km/h)
        return distance / 30.0 * 60.0;
    }

    string bookRide(const string& userId, const Location& pickup, const Location& dropoff) {
        const auto driversList = findNearbyDrivers(pickup, 10.0);
        if (driversList.empty()) {
            cout << "No drivers available nearby.\n";
            return "";
        }

        // Assign the nearest driver
        Driver* assignedDriver = driversList[0].first;
        assignedDriver->startTrip();

        const double distance = pickup.distanceTo(dropoff);
        const double price = calculatePrice(distance);

        string rideId = "RIDE_" + to_string(rides.size() + 1);
        const auto ride = new Ride(rideId, userId, assignedDriver->driverId, pickup, dropoff, price);
        ride->updateStatus("Accepted");
        rides[rideId] = ride;

        users[userId]->addRideToHistory(rideId);

        cout << "Ride booked successfully. Ride ID: " << rideId << "\n";
        return rideId;
    }

    void updateDriverLocation(const string& driverId, const Location& location) {
        if (drivers.find(driverId) != drivers.end()) {
            drivers[driverId]->updateLocation(location);
            cout << "Driver " << driverId << " location updated.\n";
        }
    }

    void trackDriverLocation(const string& rideId) {
        if (rides.find(rideId) != rides.end()) {
            const Ride* ride = rides[rideId];
            const Driver* driver = drivers[ride->driverId];
            cout << "Driver current location: (" << driver->currentLocation.latitude << ", "
                      << driver->currentLocation.longitude << ")\n";
        } else {
            cout << "Ride ID not found.\n";
        }
    }

    void cancelRide(const string& rideId, const string& userId) {
        if (rides.find(rideId) != rides.end()) {
            Ride* ride = rides[rideId];
            if (ride->userId != userId) {
                cout << "You are not authorized to cancel this ride.\n";
                return;
            }
            ride->updateStatus("Cancelled");

            // Apply cancellation fee if applicable
            constexpr double cancellationFee = 5.0; // Simplified cancellation fee
            PaymentProcessor::processRefund(ride->userId, ride->price - cancellationFee);

            if (drivers.find(ride->driverId) != drivers.end()) {
                drivers[ride->driverId]->endTrip();
            }

            cout << "Ride " << rideId << " has been cancelled. Cancellation fee: $" << cancellationFee << "\n";
        } else {
            cout << "Ride ID not found.\n";
        }
    }

    void completeRide(const string& rideId, const double driverRating) {
        if (rides.find(rideId) != rides.end()) {
            Ride* ride = rides[rideId];
            ride->updateStatus("Completed");

            if (drivers.find(ride->driverId) != drivers.end()) {
                drivers[ride->driverId]->endTrip();
                drivers[ride->driverId]->updateRating(driverRating);
            }

            PaymentProcessor::processPayment(ride->userId, ride->price);

            cout << "Ride " << rideId << " has been completed.\n";
        } else {
            cout << "Ride ID not found.\n";
        }
    }

    void displayReceipt(const string& rideId) {
        if (rides.find(rideId) != rides.end()) {
            const Ride* ride = rides[rideId];
            cout << "Receipt for Ride " << rideId << ":\n";
            cout << "User ID: " << ride->userId << "\n";
            cout << "Driver ID: " << ride->driverId << "\n";
            cout << "Pickup Location: (" << ride->pickupLocation.latitude << ", "
                      << ride->pickupLocation.longitude << ")\n";
            cout << "Drop-off Location: (" << ride->dropoffLocation.latitude << ", "
                      << ride->dropoffLocation.longitude << ")\n";
            cout << "Price: $" << fixed << setprecision(2) << ride->price << "\n";
            cout << "Status: " << ride->status << "\n";
        } else {
            cout << "Ride ID not found.\n";
        }
    }
};

int main() {
    RideService rideService;

    // Add users
    const auto user1 = new User("USER1", "Alice");
    const auto user2 = new User("USER2", "Bob");
    rideService.addUser(user1);
    rideService.addUser(user2);

    // Add drivers with more realistic details
    auto* driver1 = new Driver("DRIVER1", "Charlie", Location(10.0, 10.0), "Toyota", "Camry", "ABC123");
    auto* driver2 = new Driver("DRIVER2", "Dave", Location(10.5, 10.5), "Honda", "Accord", "XYZ789");
    rideService.addDriver(driver1);
    rideService.addDriver(driver2);

    // Scenario 1: Alice completes a ride
    cout << "\n--- Scenario 1: Alice completes a ride ---\n";
    const Location alicePickup(10.1, 10.1);
    const Location aliceDropoff(15.0, 15.0);

    // Alice checks available cabs
    cout << "\nAlice checks available cabs near her location:\n";
    rideService.displayAvailableCabs(alicePickup);

    // Alice books a ride
    const string aliceRideId = rideService.bookRide(user1->userId, alicePickup, aliceDropoff);

    if (!aliceRideId.empty()) {
        // Track driver's location as they approach Alice
        rideService.trackDriverLocation(aliceRideId);
        rideService.updateDriverLocation(driver1->driverId, Location(10.2, 10.2));
        rideService.trackDriverLocation(aliceRideId);

        // Alice completes the ride and rates the driver
        rideService.completeRide(aliceRideId, 5.0);

        // Display receipt for Alice
        rideService.displayReceipt(aliceRideId);
    }

    // Scenario 2: Bob cancels a ride
    cout << "\n--- Scenario 2: Bob cancels a ride ---\n";
    const Location bobPickup(10.3, 10.3);
    const Location bobDropoff(12.0, 12.0);

    // Bob checks available cabs
    cout << "\nBob checks available cabs near his location:\n";
    rideService.displayAvailableCabs(bobPickup);

    // Bob books a ride
    const string bobRideId = rideService.bookRide(user2->userId, bobPickup, bobDropoff);

    if (!bobRideId.empty()) {
        // Bob decides to cancel the ride before it starts
        rideService.cancelRide(bobRideId, user2->userId);

        // Optionally, Bob can check his ride history or receipts (will show canceled ride)
        rideService.displayReceipt(bobRideId);
    }

    // Users view their ride histories
    cout << "\nAlice's Ride History:\n";
    user1->displayRideHistory();

    cout << "\nBob's Ride History:\n";
    user2->displayRideHistory();

    // Clean up
    delete user1;
    delete user2;
    delete driver1;
    delete driver2;

    return 0;
}