#include <fcntl.h>
#include <iostream>
#include <iterator>
#include <list>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
//#include <curl/curl.h>
#include "AL3_lib_include/lib/include/curl/curl.h"
#include "AL3_lib_include/lib/include/libAlmondHA.h"
using namespace std;

void f1(Event *a) { cout << "event is:" << a->event << "device id" << endl; }
void f2(Device *a) {
  int lni;
  char *lnv;
  lni = a->getLastNotificationIndex();
  lnv = a->getLastNotificationIndexValue();

  cout << "\nLastNotificationIndex:" << lni
       << "\nLastNotificationIndexValue:" << lnv << endl;
}

int main() {
  int deviceid, index, i, j, OZWNode, ZigBeeShortID, ValueCount, IndexID, Type;
  char *name, *location, *ZigBeeEUI64, *Value, *IndexDataType, *IndexName,
      *Name, *AssociationTimeStamp;
  DevTech DeviceTechnology;
  DevType DeviceType;
  list<Device>::iterator it;

  HADevices hd;
  Device dobj;
  DeviceList dl;
  hd.initializeFree2();
  dl.Populate();
  for (it = dl.devices.begin(); it != dl.devices.end(); ++it) {
    i = it->getID();
    name = it->getDeviceName();
    location = it->getDeviceLocation();
    OZWNode = it->getOZWNode();
    ZigBeeShortID = it->getShortID();
    ZigBeeEUI64 = it->getZigBeeEUI64();
    AssociationTimeStamp = it->getAssociationTimeStamp();
    ValueCount = it->getValueCount();

    cout << "\ndevicid:" << i << "\ndevice name:" << name
         << "\nlocation:" << location << "\nOZWNode:" << OZWNode
         << "\nZigBeeShortID:" << ZigBeeShortID
         << "\nZigBeeEUI64:" << ZigBeeEUI64 << endl
         << "\nAssociationTimeStamp:" << AssociationTimeStamp
         << "\nValueCount:" << ValueCount << endl;

    for (j = 0; j < ValueCount; j++) {
      Value = it->getValue(j);
      Type = it->getIndexType(j);
      Name = it->getValueName(j);
      cout << "Index\t" << j << "\tValue\t" << Value << "\tType\t" << Type
           << "\tName\t" << Name << endl;
    }
    cout
        << "================================================================\n";
  }

  CURL *curl;
  CURLcode res;
  FILE *hd_src;

  //hd_src = fopen("box.txt", "r");

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if (curl) {
   // curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    // cout << "before put\n";
    /* HTTP PUT please */
    //curl_easy_setopt(curl, CURLOPT_PUT, 1L);
   // res = curl_easy_perform(curl);
   // if (res != CURLE_OK)
    //  fprintf(stderr, "curl_easy_perform() failed: %s\n",
           //   curl_easy_strerror(res));
  curl_easy_setopt(curl, CURLOPT_URL,"http://10.10.10.100/api/CM64ucPMehGrRRRraEUhDWcscyHTaQeilUNr050f/lights");
  //curl_easy_setopt(curl, CURLOPT_PUT, 1L);
 // curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
   // curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);

    //cout << "after url\n";

    res = curl_easy_perform(curl);

    cout << "after res\n";
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    curl_easy_cleanup(curl);
  }
  //fclose(hd_src);
  curl_global_cleanup();

  hd.genericCallback(f2);

  hd.eventCallback(f1);

  while (1) {
    sleep(1);
  }
}
