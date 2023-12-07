#include <boost/algorithm/string.hpp>
#include "voxblox_ros/tsdf_server.h"

#include <gflags/gflags.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "voxblox");
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, false);
  google::InstallFailureSignalHandler();
  ros::NodeHandle nh;
  ros::NodeHandle nh_private("~");

  voxblox::TsdfServer node(nh, nh_private);

  std::string bag_file(""), bag_topic("");
  nh_private.param("bag_file", bag_file, bag_file); 
  nh_private.param("bag_topic", bag_topic, bag_topic); 

  if (!bag_file.empty() && !bag_topic.empty()) {
      std::set<std::string> topics;
      boost::split(topics, bag_topic, boost::is_any_of(","));

      node.processBagFile(bag_file,topics);
  }

  ros::spin();
  return 0;
}
