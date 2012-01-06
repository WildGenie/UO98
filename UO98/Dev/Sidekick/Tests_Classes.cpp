#pragma unmanaged

#include "TestsMain.h"
#include <stdio.h>

bool Tests_Classes(void);
bool TestObjectSize(const char* name, int expected, int actual);

void Tests_Classes_Execute()
{
    InitTestLocations();

    Tests_Classes();
}

bool Tests_Classes()
{
  bool passed=TRUE;

  passed &= TestObjectSize("ListElementObject",0x10,sizeof(ListElementObject));
  passed &= TestObjectSize("ListObject",0xC,sizeof(ListObject));
  passed &= TestObjectSize("ItemObject",0x50,sizeof(ItemObject));
  passed &= TestObjectSize("ContainerObject",0x5C,sizeof(ContainerObject));
  passed &= TestObjectSize("ItemObject",0x50,sizeof(ItemObject));
  passed &= TestObjectSize("MobileObject",0x37C,sizeof(MobileObject));
  passed &= TestObjectSize("NPCObject",0x474,sizeof(NPCObject));
  passed &= TestObjectSize("GuardObject",0x480,sizeof(GuardObject));
  passed &= TestObjectSize("ShopKeeperObject",0x480,sizeof(ShopKeeperObject));
  passed &= TestObjectSize("PlayerObject",0x458,sizeof(PlayerObject));
  passed &= TestObjectSize("WeaponObject",0x58,sizeof(WeaponObject));

  //TODO: Add rest of the classes...

  if(passed)
    OnTestResult(true, "ListElement: Tests_Classes passed.");

  return passed;

}

bool TestObjectSize(const char* name, int expected, int actual)
{
  bool passed=expected==actual;
  if(!passed)
  {
    char  buffer[200];
    sprintf(buffer,"Classes: %s size expected: %d actual: %d", name,expected,actual);
    OnTestResult(false, buffer);
  }
  return passed;
}