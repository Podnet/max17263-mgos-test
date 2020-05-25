#include "mgos.h"
#include "mgos_max17263.h"
// struct MAX17263 *mx;

void battery_stats()
{
  if (mgos_max17263_battery_present())
  // without battery, status reading is 1111111111111111, so wait for Bst flag 1111111111110111
  {
    LOG(LL_INFO, ("TCU: Battery SOC intializing"));
    mgos_max17263_init();
    float capacity = mgos_max17263_get_Capacity_mAh();
    LOG(LL_INFO, ("TCU: Battery capacity in mAh = %.2f", capacity));
    float SOC = mgos_max17263_get_SOC();
    LOG(LL_INFO, ("State of Charge value is: %.2f", SOC));
    int16_t current = mgos_max17263_get_current();
    LOG(LL_INFO, ("Current is: %.2f", SOC));
    float TTE = mgos_max17263_get_TimeToEmpty();
    LOG(LL_INFO, ("Time to empty is: %.2f", TTE));
  }
  else
  {
    LOG(LL_ERROR, ("TCU: Battery SOC intializing failed."));
  }
}
extern "C"
{
  enum mgos_app_init_result mgos_app_init(void)
  {
    // setup wire library to configure max17263
    return MGOS_APP_INIT_SUCCESS;
  }
}