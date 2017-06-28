#ifndef CARLIFE_LIB_TEST_H
#define CARLIFE_LIB_TEST_H

#include<jni.h>
#include"CCarLifeLibWrapper.h"


 extern JavaVM *g_JavaVM;
 extern jobject g_obj;

 int ClickDownEvent(int x,int y);
 int ClickUpEvent(int x,int y); 	
 int OnClickEvent(int x,int y);		
 int DoubleClickEvent(int x,int y);
 int HoldOnEvent(int x,int y);	
 int MoveEvnet(int x,int y); 	

 
void SendAudioRecordData(u8* data, int len);
 int nfcarlifetest();
 void stopcarlife();

#endif
