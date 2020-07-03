#include "wr_vrep.h"

extern "C"
{
	#include "extApi.h"
}

c_wr_vrep_t c_wr_vrep;


int c_wr_vrep_t::vrep_init()
{
	int port = 66668;

	char local_host[] = "127.0.0.1";

	simxFinish(-1);
	this->clientID = simxStart(local_host, port, true, true, 5000, 5);

	if (this->clientID < 0)
	{
		return -1;
	}
	
	simxAddStatusbarMessage(this->clientID, "(from C++)C++ connected to send point cloud\r\n", simx_opmode_oneshot);

	this->inited = true;
	return 0;
}


//size:points'num    buff:x,y,z,x,y,z......  
void c_wr_vrep_t::set_point_cloud(unsigned long size, float* buff)
{
	if (this->inited == false)
	{
		return;
	}

	simxSetStringSignal(this->clientID, "point_cloud_cpp_signal", (simxUChar*)buff, size * sizeof(float) * 3, simx_opmode_oneshot);
	simxAddStatusbarMessage(this->clientID, "(from C++)\"point_cloud_cpp_signal\"send\r\n", simx_opmode_oneshot);
}