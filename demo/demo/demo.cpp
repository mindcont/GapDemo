//
// Created by ALSONTE on 2025/3/24.
//
// demo.cpp : 定义控制台应用程序的入口点。
//

#include"stdafx.h"
// open cv
#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "gapDetectionInterface.h"

using namespace std;
using namespace cv;


#include <fstream>
#include <vector>
#include <opencv2/core.hpp>

void SavePointCloudToPCDBin2(const std::vector<std::vector<cv::Point2f>>& pointClouds,
	const std::string& filename) {
	if (pointClouds.empty() || pointClouds[0].empty()) {
		std::cerr << "Error: Empty point cloud data" << std::endl;
		return;
	}

	std::ofstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file: " << filename << std::endl;
		return;
	}

	// 计算总点数
	size_t total_points = 0;
	for (const auto& cloud : pointClouds) {
		total_points += cloud.size();
	}

	// 写入标准PCD头
	file << "# .PCD v0.7 - Point Cloud Data file format\n"
		<< "VERSION 0.7\n"
		<< "FIELDS x y z\n"
		<< "SIZE 4 4 4\n"
		<< "TYPE F F F\n"
		<< "COUNT 1 1 1\n"
		<< "WIDTH " << total_points << "\n"
		<< "HEIGHT 1\n"
		<< "VIEWPOINT 0 0 0 1 0 0 0\n"
		<< "POINTS " << total_points << "\n"
		<< "DATA binary\n";

	// 写入点数据
	for (const auto& cloud : pointClouds) {
		for (const auto& point : cloud) {
			float x = point.x;
			float y = point.y;
			float z = 0.0f;
			file.write(reinterpret_cast<const char*>(&x), sizeof(float));
			file.write(reinterpret_cast<const char*>(&y), sizeof(float));
			file.write(reinterpret_cast<const char*>(&z), sizeof(float));
		}
	}

	file.close();
	std::cout << "Successfully saved " << total_points << " points to " << filename << std::endl;
}


// 保存点云数据到 PCD 文件（使用二进制格式）
void SavePointCloudToPCDBin(const std::vector<std::vector<cv::Point2f>>& pointClouds, const std::string& filename) {
	// 打开文件
	std::ofstream file(filename, std::ios::binary); // 以二进制模式打开文件
	if (!file.is_open()) {
		std::cerr << "Error: Could not open the file for writing: " << filename << std::endl;
		return;
	}

	// 写入 PCD 文件头
	file << "# .PCD v0.7 - Point Cloud Data file format\n";
	file << "VERSION 0.7\n";
	file << "FIELDS x y z\n"; // 假设保存 x, y 和 z 坐标
	file << "SIZE 4 4 4\n"; // float 类型
	file << "TYPE F F F\n"; // float 类型
	file << "COUNT 1 1 1\n"; // 每个字段的点数
	file << "WIDTH " << (pointClouds.size() * pointClouds[0].size()) << "\n"; // 总点的数量
	file << "HEIGHT 1\n"; // 单行
	file << "VIEWPOINT 0 0 0 1 0 0 0\n"; // 视点信息
	file << "POINTS " << (pointClouds.size() * pointClouds[0].size()) << "\n"; // 总点的数量
	file << "DATA binary\n"; // 数据类型为二进制

	// 写入点数据
	for (const auto& cloud : pointClouds) {
		for (const auto& point : cloud) {
			float x = point.x;
			float y = point.y;
			float z = 0.0f; // 假设 z 坐标为 0
			file.write(reinterpret_cast<const char*>(&x), sizeof(x)); // 写入 x 坐标
			file.write(reinterpret_cast<const char*>(&y), sizeof(y)); // 写入 y 坐标
			file.write(reinterpret_cast<const char*>(&z), sizeof(z)); // 写入 z 坐标
		}
	}

	// 关闭文件
	file.close();
	std::cout << "Point cloud saved to " << filename << std::endl;
}


int main()
{
	try {
		int iret;
		gapDetectionInterface mgapDetectionInterface;
		const string devicePath = "./test/";
		//打开相机
		iret = mgapDetectionInterface.openDevice(devicePath);
		if (iret != 0)
		{
			cout << "相机打开失败:" << iret << endl;
			return -1;
		}

		//设置相机参数
		string serialNumber = "leftCamera";
		cameraParams mcameraParams;
		mcameraParams.exposeTime1 = 200;
		mcameraParams.exposeTime2 = 2000;
		mcameraParams.exposeTime3 = 20000;
		mcameraParams.gain = 0;
		iret = mgapDetectionInterface.setDeviceParams(serialNumber, mcameraParams);
		string serialNumber2 = "rightCamera";
		cameraParams rightcameraParams;
		rightcameraParams.exposeTime1 = 100;
		rightcameraParams.exposeTime2 = 1000;
		rightcameraParams.exposeTime3 = 10000;
		rightcameraParams.gain = 0;
		iret = mgapDetectionInterface.setDeviceParams(serialNumber2, rightcameraParams);

		//获取点云,远中近采集校准点云
		//vector<vector<Point2f>> LeftPoint, RightPoint;
		//{
		//	int count = 0;
		//	uint16_t dataType = 1;
		//	std::vector<std::vector<cv::Point2f>> pointClouds1, pointClouds2, pointClouds3;
		//	iret = mgapDetectionInterface.getPointCloud(dataType, pointClouds1);
		//	if (iret != 0)
		//	{
		//		cout << "获取点云失败:" << iret << endl;
		//		return -1;
		//	}

		//	iret = mgapDetectionInterface.getPointCloud(dataType, pointClouds2);
		//	if (iret != 0)
		//	{
		//		cout << "获取点云失败:" << iret << endl;
		//		return -1;
		//	}

		//	iret = mgapDetectionInterface.getPointCloud(dataType, pointClouds3);
		//	if (iret != 0)
		//	{
		//		cout << "获取点云失败:" << iret << endl;
		//		return -1;
		//	}

		//	LeftPoint.push_back(pointClouds1[0]);
		//	RightPoint.push_back(pointClouds1[1]);
		//	LeftPoint.push_back(pointClouds2[0]);
		//	RightPoint.push_back(pointClouds2[1]);
		//	LeftPoint.push_back(pointClouds3[0]);
		//	RightPoint.push_back(pointClouds3[1]);
		//}

		////校准
		//vector<vector<cv::Point2f>> crossPts1, crossPts2;
		//Mat matrix2;

		//iret = mgapDetectionInterface.getMatrix(LeftPoint, RightPoint, 20, 0.2, 10, crossPts1, crossPts2, matrix2);
		//if (iret != 0)
		//{
		//	cout << "校准失败：" << iret << endl;
		//	return -1;
		//}
		uint16_t dataType = 1;
		std::vector<std::vector<cv::Point2f>> pointClouds;
		iret = mgapDetectionInterface.getPointCloud(dataType, pointClouds);

		if (iret != 0)
		{
			cout << "获取点云失败:" << iret << endl;
			return -1;
		}
		// 保存为 PLY 文件
		//生成的文件名中，配上时间后缀，形如 output_20250424145400.pcd
		std::string fileName = "output_1.pcd";

		// 输出文件名
		cout << "输出文件名：" << fileName << endl;
		cout << "获取点云成功，点云数量：" << pointClouds.size() << endl;
		SavePointCloudToPCDBin(pointClouds, fileName);

		//获取校准后的数据
		//vector<vector<Point2f>> out_pointCloud;
		//iret = mgapDetectionInterface.getCalPointCloud(matrix2, pointClouds, out_pointCloud);

		//将坐标系转水平
		Mat Rt;
		vector<vector<Point2f>> out_pointCloud2;
		iret = mgapDetectionInterface.Transferlevel(pointClouds, out_pointCloud2, Rt);

		// 保存为 PLY 文件
		//生成的文件名中，配上时间后缀，形如 output_20250424145400.pcd
		std::string fileName2 = "output_2.pcd";
		cout << "输出文件名：" << fileName2 << endl;
		cout << "获取点云成功，点云数量：" << pointClouds.size() << endl;
		SavePointCloudToPCDBin(out_pointCloud2, fileName2);

		if (iret != 0)
		{
			cout << "坐标系转水平失败：" << iret << endl;
			return -1;
		}
		//关闭设备
		iret = mgapDetectionInterface.closeDevice();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	system("pause");
	return 0;
}