#!/usr/bin/env python3

# Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
# Add license


from romea_mobile_base_bringup import urdf_description
import sys

if __name__ == "__main__":

    argv = sys.argv

    parameters = {}
    for argument in argv[1:]:
        name, value = argument.split(":")
        parameters[name] = value

    mode = parameters["mode"]
    robot_namespace = parameters["robot_namespace"]
    meta_description_file_path = parameters["meta_description_file_path"]
    print(urdf_description(robot_namespace, mode, meta_description_file_path))
