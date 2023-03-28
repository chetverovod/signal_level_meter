/* File mstest3.c Signal Level Meter. */

/* Include filters header files. */ 
#include <mediastreamer2/msfilter.h>
#include <mediastreamer2/msticker.h>
#include <mediastreamer2/dtmfgen.h>
#include <mediastreamer2/mssndcard.h>
#include <mediastreamer2/msvolume.h>

int main()
{
  MSFactory *mf;  /* Factory of Mediastremer's filters. */
  mf = ms_factory_new();
  ms_factory_init_voip(mf);
  
    /* Instantiating filters. */
    MSFilter *voidsource = ms_factory_create_filter(mf, MS_VOID_SOURCE_ID);
    MSFilter *dtmfgen = ms_factory_create_filter(mf, MS_DTMF_GEN_ID);
    MSFilter  ms_factory_create_filter(mf, MS_VOLUME_ID);
    MSSndCardManager *scm; /* Soundcards manager. */
    scm = ms_factory_get_snd_card_manager(mf);
    MSSndCard *card_playback = ms_snd_card_manager_get_default_card(scm);
    MSFilter  *snd_card_write = ms_snd_card_create_writer(card_playback);
  
    //MSSndCard *card_playback=ms_snd_card_manager_get_default_card(ms_snd_card_manager_get());
    //MSFilter  *snd_card_write=ms_snd_card_create_writer(card_playback);
  
    /* Create a ticker. */
    MSTicker *ticker=ms_ticker_new();
  
    /* We connect filters in a chain. */
    ms_filter_link(voidsource, 0, dtmfgen, 0);
    ms_filter_link(dtmfgen, 0, volume, 0);
    ms_filter_link(volume, 0, snd_card_write, 0);
  
  /* Connect the clock source. */
    ms_ticker_attach(ticker,voidsource);
    MSDtmfGenCustomTone dtmf_cfg;
   /* We set the name of our signal, remembering that in the array we must leave room for a zero, which marks the end of the line. */
    strncpy(dtmf_cfg.tone_name, "busy", sizeof(dtmf_cfg.tone_name));
    dtmf_cfg.duration=1000;
    dtmf_cfg.frequencies[0]=440; /* We will generate one tone, set the frequency of the second tone to 0.*/
    dtmf_cfg.frequencies[1]=0;
    dtmf_cfg.amplitude=1.0; /* This sine amplitude should correspond to a measurement result of 0.707.*/
    dtmf_cfg.interval=0.;
    dtmf_cfg.repeat_count=0.;
   /* Turn on the sound generator. */
   ms_filter_call_method(dtmfgen, MS_DTMF_GEN_PLAY_CUSTOM, (void*)&dtmf_cfg);
   /* We give half a second time for the meter to accumulate data. */
   ms_usleep(500000);
   /* Reading the measurement result. */
  float level=0;
   ms_filter_call_method(volume, MS_VOLUME_GET_LINEAR,&level);
   printf("The amplitude of the sine %f volts corresponds to the rms value of %f volts.\n", dtmf_cfg.amplitude, level);
}
