/*This code initializes an timer using RTC1. The RTC uses the Low Frequency Clock (LFCLK)
Multiple timer instances can be created using RTC*/

uint button1,button2;
uint timerStarted;

void repeated_timer_handler(void * p_context);
uint vPeriodicEventHandlerStart(app_timer_id_t timer_id,uint timeInUs, void (*callbackFn)());
uint vPeriodicEventHandlerStop(app_timer_id_t timer_id);

APP_TIMER_DEF(m_repeated_timer_in_us);/*create a time handler for repeated timer used call callbackFunction*/

main()
{
    /*nrf_drv_clock_init():Function starting the internal LFCLK oscillator.
    This is needed by RTC1 which is used by the Application Timer*/
    nrf_drv_clock_init();
    
    /*initialize gpio for button 1 and button 2.*/
    
    /*app_timer_init():Initialize Application Timer,before making any calls 
    to application timer API's*/
    app_timer_init();
    
    while(1)
    {
         if(button1 == 1)/*read gpio status when button1 is pressed and start 509us timer*/
         {
            if(vPeriodicEventHandlerStart(m_repeated_timer_in_us,509,vCallbackFn))
            {
                timerStarted = 1;
                print("timer started successfully");
            }
            else
            {
                timerStarted = 0;
                print("Error:timer not started");
            }
         }
         
         if(button2 == 1)/*read gpio status when button2 is pressed and stop 509us timer*/
         {
            if(timerStarted==1)
            {
                 if(vPeriodicEventHandlerStop(m_repeated_timer_in_us))
                 {
                      print("timer stopped successfully");
                 }
                 else
                 {
                      print("Error:timer not stopped");
                 }
            }
            else
            {
                 print("no timer is running")
            }
         }
    }
    
}

/*Funtion Name: vCallbackFn
  Function Arguments:void * p - third parameter in the api app_timer_create(),
                    a general-purpose pointer that is passed to the timeout handler callback function.
  detail:Function prints a incremented counter value when ever it is called/

void vCallbackFn(void * p)
{
    static uint i;
    print(i);
    i++; 
}

/*Funtion Name:vPeriodicEventHandlerStart
  Function Arguments:app_timer_id_t timer_id -application time Handler Instance,
                     uint timeInUs : timeOut in us.
                     void (*callbackFn)() : callback function
  detail:Function creates a timer in repeated mode and every time the timeOut happens
                   the callback is called*/
                   
uint vPeriodicEventHandlerStart(app_timer_id_t timer_id,uint timeInUs, void (*callbackFn)())
{
     uint err_code=0;
     err_code = app_timer_create(&timer_id,APP_TIMER_MODE_REPEATED,callbackFn);
     if(!(err_code))
     {
          return 0;
     }
     err_code = app_timer_start(timer_id, APP_TIMER_TICKS(timeInUs), NULL);
     if(!(err_code))
     {
          return 0;
     }
     return 1;
}

/*Funtion Name:vPeriodicEventHandlerStop
  Function Arguments:app_timer_id_t timer_id - application time Handler Instance,
  detail:Function stops the timer*/
                   
uint vPeriodicEventHandlerStop(app_timer_id_t timer_id)
{
     uint err_code=0;
     err_code = app_timer_stop(timer_id);
     if(!(err_code))
     {
          return 0;
     }
     return 1;
}
