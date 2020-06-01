#include "mgos.h"
#include "mgos_max17263.h"
// struct MAX17263 *mx;



/*! \mainpage Battery SOC testing
 *
 * \section Documentation
 *
 * This is a test app to read battery stats like capacity, current , time to empty etc.
 */




/**> Get battery stats. */
void battery_stats_cb()
{
  if (mgos_max17263_battery_present())
  // without battery, status reading is 1111111111111111, so wait for Bst flag 1111111111110111
  {
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

  /**> MongooseOS app initialization function. */
  enum mgos_app_init_result mgos_app_init(void)
  {
    LOG(LL_INFO, ("TCU: Battery SOC intializing"));
    mgos_max17263_init();
    // setup wire library to configure max17263
    mgos_set_timer(
      1000,
      MGOS_TIMER_REPEAT,
      battery_stats_cb,
      NULL);  
    return MGOS_APP_INIT_SUCCESS;
  }
}