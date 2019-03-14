#include <BasicInfo.h>
#include <iostream>
#include <json.hpp>

using nlohmann::json;
using namespace std;

int main() {
  GameInfo::Admin test("fuck", "fuck", 50, 50);
  json j = json::parse("[1,false,\"data\"]");
  std::cout << j << endl;
  return 0;
}
