#include<iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

extern "C"{
#include "extApi.h"
}

#include <conio.h>

#include "wr_vrep.h"

int main(int argc, char** argv) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    //�򿪵����ļ�
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("rabbit.pcd", *cloud) == -1) 
    {
        PCL_ERROR("error at open pcd file\n");
        return(-1);
    }
    std::cout << "total points: "<<cloud->points.size() << std::endl;
    

    //��ʾ����
    if (false)
    {
        pcl::visualization::CloudViewer viewer("viewer");
        viewer.showCloud(cloud);
        while (0 == viewer.wasStopped());
    }

    if (c_wr_vrep.vrep_init() < 0)
    {
        cout << "vrep_init_failed" << endl;
    }
    else
    {
        cout << "vrep_init_success!" << endl;
    }

    //vrep���͵���
    while (true)
    {
        char c;
        c = _getch();
        if (c == 's')
        {
            c_wr_vrep.vrep_init();//Ϊ��Vrep����ֹͣ���ٴ����з��棬������Ʋ�����������C++���ɵ�exe�����������½���һ����Vrep������
            cout << "send point cloud for once" << endl;
            float* buff;
            buff = (float*)malloc(sizeof(float) * cloud->points.size() * 3);
            if (buff == NULL)
            {
                cout << "malloc failed???" << endl;
            }
            else
            {
                cout << "malloc success" << endl;
                int i;
                for (i = 0; i < cloud->points.size();i++)
                {
                    buff[i * 3 + 0] = (float)cloud->points[i].x;
                    buff[i * 3 + 1] = (float)cloud->points[i].y;
                    buff[i * 3 + 2] = (float)cloud->points[i].z;
                }
                c_wr_vrep.set_point_cloud(cloud->points.size(), buff);
                free(buff);
                cout << "free ed" << endl;
            }
            Sleep(1000);
        }
        else if (c == 'e')
        {
            cout << "exit" << endl;
            break;
        }

    }
    system("pause");
    return 0;
}