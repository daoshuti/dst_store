/*************************************************************************
 @Author: wanghan
 @Created Time : Tue 11 Apr 2017 06:00:32 PM CST
 @File Name: lightpointer.cpp
 @Description:
 ************************************************************************/
#include <stdio.h>
#include <utils/RefBase.h>

using namespace android;

class LightClass : public LightRefBase<LightClass>
{
public:
	LightClass()
	{
		printf("Construct LightClass Object.\n");
	}
	virtual ~LightClass()
	{
		printf("Destroy LightClass Object.\n");
	}
};

int main(int argc, const char *argv[])
{
	LightClass *pLightClass = new LightClass();
	sp<LightClass> lpOut = pLightClass;

	printf("Light Ref Count: %d.\n", pLightClass->getStrongCount());

	{
		sp<LightClass> lpInner = lpOut;
		printf("Light Ref Count: %d.\n", pLightClass->getStrongCount());
	}

	printf("Light Ref Count: %d.\n", pLightClass->getStrongCount());

	return 0;
}
