#pragma once
typedef class
{
public:
	bool inited;
	int clientID;
	int vrep_init();
	void set_point_cloud(unsigned long size, float* buff);
}c_wr_vrep_t;

extern c_wr_vrep_t c_wr_vrep;