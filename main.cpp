#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <map>



std::mutex display;


void Swimmer(int speed, const std::string& name, std::vector<std::string>& results){
    int length = 100;
    while(length){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        length -= speed;
        if(length < 0) length = 0;
        display.lock();
        std::cout << "The swimmer " << name << " swam " << 100 - length << " meters." << std::endl;
        if(length == 0) results.emplace_back(name);
        display.unlock();
    }

}
int main() {
    std::map<std::string , int> swimmersData;
    std::vector<std::string> champion;
    std::array<std::thread , 6> swimmers;
    for(int i = 0; i < 6; ++i){
        int speed;
        std::string name;
        std::cout << "Enter the swimmer's #" << i + 1 << " name: ";
        std::cin >> name;
        std::cout << "Enter the swimmer's #" << i + 1 << " speed: ";
        std::cin >> speed;
        swimmersData.insert(std::make_pair(name, speed));

    }
    auto it = swimmersData.begin();
    for(auto & el : swimmers) {
        el = std::thread(Swimmer,it->second, std::ref(it->first), std::ref(champion));
        el.detach();
        it++;
    }
    bool theEnd = false;
    do{
        std::this_thread::sleep_for(std::chrono::seconds(6));
        if(champion.size() == 6) theEnd = true;
    }while(!theEnd);
    for(auto & el : champion) std::cout << el << std::endl;
    return 0;
}
