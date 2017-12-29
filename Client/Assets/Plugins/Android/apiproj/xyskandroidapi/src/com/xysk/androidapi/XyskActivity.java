package com.xysk.androidapi;

import java.net.NetworkInterface;
import java.util.Collections;
import java.util.List;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;

public class XyskActivity extends Activity {

	Class<?> unityActivity = null;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }
    
    @SuppressLint("NewApi") public static String getMACAddress(String interfaceName) {
        try {
            List<NetworkInterface> interfaces = Collections.list(NetworkInterface.getNetworkInterfaces());
            for (NetworkInterface intf : interfaces) {
                if (interfaceName != null) {
                    if (!intf.getName().equalsIgnoreCase(interfaceName)) continue;
                }
                byte[] mac = intf.getHardwareAddress();
                if (mac==null) return "";
                StringBuilder buf = new StringBuilder();
                for (int idx=0; idx<mac.length; idx++)
                    buf.append(String.format("%02X:", mac[idx]));       
                if (buf.length()>0) buf.deleteCharAt(buf.length()-1);
                return buf.toString();
            }
        } catch (Exception ex) { } // for now eat exceptions
        return "";
    }
    
 // ��Ƶ��ȡԴ
    public static int audioSource = MediaRecorder.AudioSource.MIC;
    // ������Ƶ�����ʣ�44100��Ŀǰ�ı�׼������ĳЩ�豸��Ȼ֧��22050��16000��11025
    public static int sampleRateInHz = 44100;
    // ������Ƶ��¼�Ƶ�����CHANNEL_IN_STEREOΪ˫������CHANNEL_CONFIGURATION_MONOΪ������
    public static int channelConfig = AudioFormat.CHANNEL_IN_STEREO;
    // ��Ƶ���ݸ�ʽ:PCM 16λÿ����������֤�豸֧�֡�PCM 8λÿ����������һ���ܵõ��豸֧�֡�
    public static int audioFormat = AudioFormat.ENCODING_PCM_16BIT;
    // �������ֽڴ�С
    public static int bufferSizeInBytes = 0;
    /**
     * �ж����Ƿ���¼��Ȩ��
     */
    public static boolean isHasPermission(){
        bufferSizeInBytes = 0;
        bufferSizeInBytes = AudioRecord.getMinBufferSize(sampleRateInHz,
                channelConfig, audioFormat);
        AudioRecord audioRecord =  new AudioRecord(audioSource, sampleRateInHz,
                channelConfig, audioFormat, bufferSizeInBytes);
        //��ʼ¼����Ƶ
        try{
            // ��ֹĳЩ�ֻ���������������
            audioRecord.startRecording();
        }catch (IllegalStateException e){
            e.printStackTrace();
        }
        /**
         * ���ݿ�ʼ¼���ж��Ƿ���¼��Ȩ��
         */
        if (audioRecord.getRecordingState() != AudioRecord.RECORDSTATE_RECORDING) {
            
            return false;
        }
        audioRecord.stop();
        audioRecord.release();
        audioRecord = null;

        return true;
    }
    
    /**
     * ��ȡ�汾��
     * @return ��ǰӦ�õİ汾��
     */
    public String getVersion() {
        try {
            PackageManager manager = this.getPackageManager();
            PackageInfo info = manager.getPackageInfo(this.getPackageName(), 0);
            return info.versionName;
        } catch (Exception e) {
            e.printStackTrace();
            return "";
        }
    }
}
