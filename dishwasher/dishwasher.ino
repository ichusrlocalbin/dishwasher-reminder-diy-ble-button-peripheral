#include <BLE_API.h>

#define DEVICE_NAME       "Dishwasher_BLE"
#define TXRX_BUF_LEN      20
BLE                       ble;
Ticker                    ticker1s;

static const uint8_t service_uuid[]        = { 0x43, 0x54, 0, 0, 0x3a, 0xc6, 0x4f, 0x1e, 0xb7, 0xdc, 0x75, 0x99, 0xc8, 0x9b, 0x49, 0x45 };
static const uint8_t service_chars_uuid[]  = { 0x43, 0x54, 0, 2, 0x3a, 0xc6, 0x4f, 0x1e, 0xb7, 0xdc, 0x75, 0x99, 0xc8, 0x9b, 0x49, 0x45 };
static const uint8_t service_uuid_reverse[]        = { 0x45, 0x49, 0x9b, 0xc8, 0x99, 0x75, 0xdc, 0xb7, 0x1e, 0x4f, 0xc6, 0x3a, 0, 0, 0x54, 0x43 };

uint8_t chars_value[TXRX_BUF_LEN] = { 's', 't', 'a', 'r', 't' };

GattCharacteristic  characteristic(service_chars_uuid, chars_value, 5, TXRX_BUF_LEN, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ);
GattCharacteristic *uartChars[] = { &characteristic };
GattService         uartService(service_uuid, uartChars, sizeof(uartChars) / sizeof(GattCharacteristic *));

void disconnectionCallBack(const Gap::DisconnectionCallbackParams_t *params) {
  Serial.print("Disconnected hande : ");
  Serial.println(params->handle, HEX);
  Serial.print("Disconnected reason : ");
  Serial.println(params->reason, HEX);
  Serial.println("Restart advertising ");
  ble.startAdvertising();
}

void connectionCallBack(const Gap::ConnectionCallbackParams_t *params) {
  uint8_t index;
  if(params->role == Gap::PERIPHERAL) {
    Serial.println("Peripheral ");
  }

  Serial.print("The conn handle : ");
  Serial.println(params->handle, HEX);
  Serial.print("The conn role : ");
  Serial.println(params->role, HEX);

  Serial.print("The peerAddr type : ");
  Serial.println(params->peerAddrType, HEX);
  Serial.print("  The peerAddr : ");
  for(index=0; index<6; index++) {
    Serial.print(params->peerAddr[index], HEX);
    Serial.print(" ");
  }
  Serial.println(" ");

  Serial.print("The ownAddr type : ");
  Serial.println(params->ownAddrType, HEX);
  Serial.print("  The ownAddr : ");
  for(index=0; index<6; index++) {
    Serial.print(params->ownAddr[index], HEX);
    Serial.print(" ");
  }
  Serial.println(" ");

  Serial.print("The min connection interval : ");
  Serial.println(params->connectionParams->minConnectionInterval, HEX);
  Serial.print("The max connection interval : ");
  Serial.println(params->connectionParams->maxConnectionInterval, HEX);
  Serial.print("The slaveLatency : ");
  Serial.println(params->connectionParams->slaveLatency, HEX);
  Serial.print("The connectionSupervisionTimeout : ");
  Serial.println(params->connectionParams->connectionSupervisionTimeout, HEX);
}


void task_handle(void) {
  //  Serial.println("Task handle ");
}

void setAdvertisement(void) {
  ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
  ble.accumulateAdvertisingPayload(GapAdvertisingData::SHORTENED_LOCAL_NAME,(const uint8_t *)"d_w", 3);
  // ble.accumulateAdvertisingPayload(GapAdvertisingData::SHORTENED_LOCAL_NAME,(const uint8_t *)"dishwasher", 10);
  ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_128BIT_SERVICE_IDS,(const uint8_t *)service_uuid_reverse, sizeof(service_uuid_reverse));
  ble.accumulateScanResponse(GapAdvertisingData::COMPLETE_LOCAL_NAME,(const uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME) - 1);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Start ");
  pinMode(D13, OUTPUT);
  // Init timer task
  // ticker1s.attach(task_handle, 1);
  ble.init();
  ble.onConnection(connectionCallBack);
  ble.onDisconnection(disconnectionCallBack);

  setAdvertisement();
  ble.setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
  ble.addService(uartService);
  ble.setDeviceName((const uint8_t *)DEVICE_NAME);
  ble.setTxPower(4);
  // set adv_interval, 100ms in multiples of 0.625ms.
  ble.setAdvertisingInterval(160);
  ble.setAdvertisingTimeout(0);
  Serial.print("BLE stack verison is : ");
  Serial.println(ble.getVersion());
  ble.startAdvertising();
  Serial.println("start advertising ");
}

void loop() {
  ble.waitForEvent();
}

