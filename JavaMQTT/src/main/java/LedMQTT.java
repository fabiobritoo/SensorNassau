import java.util.concurrent.TimeUnit;

import org.fusesource.mqtt.client.BlockingConnection;
import org.fusesource.mqtt.client.MQTT;
import org.fusesource.mqtt.client.QoS;

public class LedMQTT {

	public static void main(String[] args) throws Exception {
				
		//__ Informações do dispositivo
		
		String DEVICE_TYPE = "NodeMCU";
		String DEVICE_ID = "Led";
		
		
		//__ Informações da conexão com o servidor
		
		String ORG = "kh6pjf";
		String authMeth = "a-kh6pjf-4cgid85ysw";
		String TOKEN = "i-D1Dpto0t+g5wzV+H";
		
		//__ Variáveis de conexão com o servidor (Não customizaveis)
		
		String server   = ORG + ".messaging.internetofthings.ibmcloud.com";
		String topic    = "iot-2/type/" + DEVICE_TYPE + "/id/" + DEVICE_ID + "/evt/1-anl/fmt/json";
		String token   = TOKEN;
		String clientId = "a:" + ORG + ":" + DEVICE_ID;
		
		
		MQTT mqtt = new MQTT();
		
		mqtt.setCleanSession(true);
		mqtt.setHost(server, 1883);
		mqtt.setClientId(clientId);
		mqtt.setUserName(authMeth);
		mqtt.setPassword(TOKEN);
			
			
		BlockingConnection connection = mqtt.blockingConnection();
		connection.connect();
		
		
		BuildPayload payload = new BuildPayload(1);
			
		while (true) {
						
			byte[] msg = payload.build();
			connection.publish(topic, msg, QoS.AT_LEAST_ONCE, false);
			TimeUnit.SECONDS.sleep(2);				
		
			
		}
			
		
	}
	
}

	class BuildPayload {
		
		private int value;
		public BuildPayload(int value) {
			this.value = value;
		}
		
		public byte[] build() {
			if (Math.random() > 0.5) value = 1;
			else value = 0;
									 
	        String payload =  "{\"d\":{\"" + "led" + "\":";
			payload += value;
			payload += "}}"; 
			System.out.print("Sending payload: ");
			System.out.println(payload);
			return payload.getBytes();
			
		}
		
	}
