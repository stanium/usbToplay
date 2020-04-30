package com.vsoon.airplay;
import android.util.Log;

import java.net.Inet4Address;
import java.net.Inet6Address;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;

import javax.jmdns.JmDNS;
import javax.jmdns.ServiceInfo;

public class AirPlayServer implements Runnable {
    private static final String TAG="AirPlayServer";
    //用于音频
    static final String AIR_TUNES_SERVICE_TYPE = "_raop._tcp.local.";

    /*

     */
    static final String RAOP_TXTVERS= "1";
    static final String RAOP_CH= "2"             /* Audio channels: 2 */;
    static final String RAOP_CN= "0,1,2,3";           /* Audio codec: PCM, ALAC, AAC, AAC ELD */
    static final String RAOP_ET= "0,3,5";           /* Encryption type: None, FairPlay, FairPlay SAPv2.5 */
    static final String RAOP_VV ="2";
    static final String RAOP_FT ="0x5A7FFFF7,0x1E";
    static final String RAOP_RHD= "5.6.0.0";
    static final String RAOP_SF= "0x4";
    static final String RAOP_SV= "false";
    static final String RAOP_DA= "true";
    static final String RAOP_SR= "44100";         /* Sample rate: 44100 */
    static final String RAOP_SS= "16";            /* Sample size: 16 */
    static final String RAOP_VS= "220.68";
    static final String RAOP_TP= "UDP";           /* Transport protocol. Possible values: UDP or TCP or TCP,UDP */
    static final String RAOP_MD= "0,1,2";         /* Metadata: text, artwork, progress */
    static final String RAOP_VN= "65537";
    static final String RAOP_PK= "b07727d6f6cd6e08b58ede525ec3cdeaa252ad9f683feb212ef8a205246554e7";
    static final String AIRPLAY_FEATURES= "0x5A7FFFF7,0x1E";
    static final String AIRPLAY_SRCVERS= "220.68";
    static final String AIRPLAY_FLAGS= "0x4";
    static final String AIRPLAY_VV= "2";
    static final String AIRPLAY_PK= "b07727d6f6cd6e08b58ede525ec3cdeaa252ad9f683feb212ef8a205246554e7";
    static final String AIRPLAY_PI= "2e388006-13ba-4041-9a67-25dd4a43d536";

    /**
     * The AirTunes/RAOP M-DNS service properties (TXT record)
     */
    static final Map<String, String> AIRTUNES_SERVICE_PROPERTIES = map(
            "txtvers", "1",
            "tp", "UDP",
            "ch", "2",
            "ss", "16",
            "sr", "44100",
            "pw", "false",
            "sm", "false",
            "sv", "false",
            "ek", "1",
            "et", "0,1",
            "cn", "0,1",
            "vn", "3"
    );
    //用于视频
    static final String AIR_PLAY_SERVICE_TYPE="_airplay._tcp.local.";

    static final Map<String,String> AIRPLAY_SERVICE_PROPERTIES = map(
      "deviceid","",
            "features","0x5A7FFFF7,0x1E",
            "flags","0x4",
            "model","AppleTV2,1",
            "pk",AIRPLAY_PK,
            "pi",AIRPLAY_PI,
            "srcvers",AIRPLAY_SRCVERS,
            "vv",AIRPLAY_VV
    );

    /*
    int utils_hwaddr_airplay(char *str, int strlen, const char *hwaddr, int hwaddrlen)
    {
        int i,j;

        // Check that our string is long enough
        if (strlen == 0 || strlen < 2*hwaddrlen+hwaddrlen)
            return -1;

        //Convert hardware address to hex string
        for (i=0,j=0; i<hwaddrlen; i++) {
            int hi = (hwaddr[i]>>4) & 0x0f;
            int lo = hwaddr[i] & 0x0f;

            if (hi < 10) str[j++] = '0' + hi;
            else         str[j++] = 'a' + hi-10;
            if (lo < 10) str[j++] = '0' + lo;
            else         str[j++] = 'a' + lo-10;

            str[j++] = ':';
        }

        // Add string terminator
        if (j != 0) j--;
        str[j++] = '\0';
        return j;
    }
    */


    /**
     * JmDNS instances (one per IP address). Used to unregister the mDNS services
     * during shutdown.
     */
    protected List<JmDNS> jmDNSInstances;

    /**
     * The AirTunes/RAOP RTSP port
     */
    private int rtspPort = 5000; //default value

    private static AirPlayServer instance = null;
    public static AirPlayServer getIstance(){
        if(instance == null){
            instance = new AirPlayServer();
        }
        return instance;
    }

    public int getRtspPort() {
        return rtspPort;
    }
    @Override
    public void run() {
        startService();
    }

    private void startService()
    {
        NetworkUtils networkUtils =NetworkUtils.getInstance();
        String hostName = networkUtils.getHostUtils();
        String hardwareAddressString= networkUtils.getHardwareAddressString();
        Log.d(TAG,"hostName="+hostName+",hardwareAddressString="+hardwareAddressString);

        try {
            synchronized (jmDNSInstances) {
                for(final NetworkInterface iface: Collections.list(NetworkInterface.getNetworkInterfaces())) {
                    if(iface.isLoopback()){
                        continue;
                    }
                    if(iface.isPointToPoint()){
                        continue;
                    }
                    if(!iface.isUp()){
                        continue;
                    }
                    for(final InetAddress addr:Collections.list(iface.getInetAddresses())) {
                        if ( ! (addr instanceof Inet4Address) && ! (addr instanceof Inet6Address) ){
                            continue;
                        }

                        try {
                            final JmDNS jmDNS = JmDNS.create(addr, hostName+"-jmdns");
                            jmDNSInstances.add(jmDNS);
                            final ServiceInfo airTunesServiceInfo =ServiceInfo.create(
                                    AIR_TUNES_SERVICE_TYPE,
                                    hardwareAddressString+"@"+hostName+"("+iface.getName()+")",
                                    getRtspPort(),
                                    0,0,
                                    AIRTUNES_SERVICE_PROPERTIES
                            );
                            jmDNS.registerService(airTunesServiceInfo);
                            Log.d(TAG,"Registered AirTunes service '" + airTunesServiceInfo.getName() + "' on " + addr);

                            final ServiceInfo airPlayServiceInfo =ServiceInfo.create(
                                    AIR_PLAY_SERVICE_TYPE,
                                    hardwareAddressString+"@"+hostName+"("+iface.getName()+")",
                                    getRtspPort()+1,
                                    0,0,
                                    AIRPLAY_SERVICE_PROPERTIES

                            );
                        }
                        catch (final Throwable e) {
                            Log.d(TAG, "Failed to publish service on " + addr, e);
                        }
                    }
                }
            }
        }
        catch (SocketException e) {
            Log.d(TAG, "Failed register mDNS services", e);
        }
    }

    /**
     * Map factory. Creates a Map from a list of keys and values
     *
     * @param keys_values key1, value1, key2, value2, ...
     * @return a map mapping key1 to value1, key2 to value2, ...
     */
    private static Map<String, String> map(final String... keys_values) {
        assert keys_values.length % 2 == 0;
        final Map<String, String> map = new java.util.HashMap<String, String>(keys_values.length / 2);
        for(int i=0; i < keys_values.length; i+=2)
            map.put(keys_values[i], keys_values[i+1]);
        return Collections.unmodifiableMap(map);
    }

}
