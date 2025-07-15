//
// Created by ALSONTE on 2025/3/24.
//
// demo.cpp : �������̨Ӧ�ó������ڵ㡣
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

	// �����ܵ���
	size_t total_points = 0;
	for (const auto& cloud : pointClouds) {
		total_points += cloud.size();
	}

	// д���׼PCDͷ
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

	// д�������
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


// ����������ݵ� PCD �ļ���ʹ�ö����Ƹ�ʽ��
void SavePointCloudToPCDBin(const std::vector<std::vector<cv::Point2f>>& pointClouds, const std::string& filename) {
	// ���ļ�
	std::ofstream file(filename, std::ios::binary); // �Զ�����ģʽ���ļ�
	if (!file.is_open()) {
		std::cerr << "Error: Could not open the file for writing: " << filename << std::endl;
		return;
	}

	// д�� PCD �ļ�ͷ
	file << "# .PCD v0.7 - Point Cloud Data file format\n";
	file << "VERSION 0.7\n";
	file << "FIELDS x y z\n"; // ���豣�� x, y �� z ����
	file << "SIZE 4 4 4\n"; // float ����
	file << "TYPE F F F\n"; // float ����
	file << "COUNT 1 1 1\n"; // ÿ���ֶεĵ���
	file << "WIDTH " << (pointClouds.size() * pointClouds[0].size()) << "\n"; // �ܵ������
	file << "HEIGHT 1\n"; // ����
	file << "VIEWPOINT 0 0 0 1 0 0 0\n"; // �ӵ���Ϣ
	file << "POINTS " << (pointClouds.size() * pointClouds[0].size()) << "\n"; // �ܵ������
	file << "DATA binary\n"; // ��������Ϊ������

	// д�������
	for (const auto& cloud : pointClouds) {
		for (const auto& point : cloud) {
			float x = point.x;
			float y = point.y;
			float z = 0.0f; // ���� z ����Ϊ 0
			file.write(reinterpret_cast<const char*>(&x), sizeof(x)); // д�� x ����
			file.write(reinterpret_cast<const char*>(&y), sizeof(y)); // д�� y ����
			file.write(reinterpret_cast<const char*>(&z), sizeof(z)); // д�� z ����
		}
	}

	// �ر��ļ�
	file.close();
	std::cout << "Point cloud saved to " << filename << std::endl;
}


int main()
{
	try {
		int iret;
		gapDetectionInterface mgapDetectionInterface;
		const string devicePath = "./test/";
		//�����
		iret = mgapDetectionInterface.openDevice(devicePath);
		if (iret != 0)
		{
			cout << "�����ʧ��:" << iret << endl;
			return -1;
		}

		//�����������
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

		//��ȡ����,Զ�н��ɼ�У׼����
		//vector<vector<Point2f>> LeftPoint, RightPoint;
		//{
		//	int count = 0;
		//	uint16_t dataType = 1;
		//	std::vector<std::vector<cv::Point2f>> pointClouds1, pointClouds2, pointClouds3;
		//	iret = mgapDetectionInterface.getPointCloud(dataType, pointClouds1);
		//	if (iret != 0)
		//	{
		//		cout << "��ȡ����ʧ��:" << iret << endl;
		//		return -1;
		//	}

		//	iret = mgapDetectionInterface.getPointCloud(dataType, pointClouds2);
		//	if (iret != 0)
		//	{
		//		cout << "��ȡ����ʧ��:" << iret << endl;
		//		return -1;
		//	}

		//	iret = mgapDetectionInterface.getPointCloud(dataType, pointClouds3);
		//	if (iret != 0)
		//	{
		//		cout << "��ȡ����ʧ��:" << iret << endl;
		//		return -1;
		//	}

		//	LeftPoint.push_back(pointClouds1[0]);
		//	RightPoint.push_back(pointClouds1[1]);
		//	LeftPoint.push_back(pointClouds2[0]);
		//	RightPoint.push_back(pointClouds2[1]);
		//	LeftPoint.push_back(pointClouds3[0]);
		//	RightPoint.push_back(pointClouds3[1]);
		//}

		////У׼
		//vector<vector<cv::Point2f>> crossPts1, crossPts2;
		//Mat matrix2;

		//iret = mgapDetectionInterface.getMatrix(LeftPoint, RightPoint, 20, 0.2, 10, crossPts1, crossPts2, matrix2);
		//if (iret != 0)
		//{
		//	cout << "У׼ʧ�ܣ�" << iret << endl;
		//	return -1;
		//}
		uint16_t dataType = 1;
		std::vector<std::vector<cv::Point2f>> pointClouds;
		iret = mgapDetectionInterface.getPointCloud(dataType, pointClouds);

		if (iret != 0)
		{
			cout << "��ȡ����ʧ��:" << iret << endl;
			return -1;
		}
		// ����Ϊ PLY �ļ�
		//���ɵ��ļ����У�����ʱ���׺������ output_20250424145400.pcd
		std::string fileName = "output_1.pcd";

		// ����ļ���
		cout << "����ļ�����" << fileName << endl;
		cout << "��ȡ���Ƴɹ�������������" << pointClouds.size() << endl;
		SavePointCloudToPCDBin(pointClouds, fileName);

		//��ȡУ׼�������
		//vector<vector<Point2f>> out_pointCloud;
		//iret = mgapDetectionInterface.getCalPointCloud(matrix2, pointClouds, out_pointCloud);

		//������ϵתˮƽ
		Mat Rt;
		vector<vector<Point2f>> out_pointCloud2;
		iret = mgapDetectionInterface.Transferlevel(pointClouds, out_pointCloud2, Rt);

		// ����Ϊ PLY �ļ�
		//���ɵ��ļ����У�����ʱ���׺������ output_20250424145400.pcd
		std::string fileName2 = "output_2.pcd";
		cout << "����ļ�����" << fileName2 << endl;
		cout << "��ȡ���Ƴɹ�������������" << pointClouds.size() << endl;
		SavePointCloudToPCDBin(out_pointCloud2, fileName2);

		if (iret != 0)
		{
			cout << "����ϵתˮƽʧ�ܣ�" << iret << endl;
			return -1;
		}
		//�ر��豸
		iret = mgapDetectionInterface.closeDevice();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	system("pause");
	return 0;
}