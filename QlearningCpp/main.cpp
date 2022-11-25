#include"uavQLearning.h"

int main()
{
    std::cout << "Please press Enter to arm the drone"; std::cin.get();
    msr::airlib::MultirotorRpcLibClient client;

    client.enableApiControl(true);
    client.armDisarm(true);

    std::vector<Barrier> vecBarr;
    std::vector<Router> vecRoute;
    std::vector<RewardMatrix> vecRewardMatrix;
    std::vector<QMatrix> vecQMatrix;
    Drone drone;

    std::cout << "Please press Enter to train"; std::cin.get();
    train(vecBarr, vecRoute, vecRewardMatrix, vecQMatrix, drone, client);
    std::cout << "Please press Enter to validate"; std::cin.get();
    validate(vecQMatrix, vecRoute, drone, client);

    client.armDisarm(false);
    client.enableApiControl(false);
    
}