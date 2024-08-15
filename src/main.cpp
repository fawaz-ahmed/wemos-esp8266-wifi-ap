// #define IP_NAPT 1
// #define CONFIG_IPV6_STATIC_ADDR "2001:0410:0:1:0:0:0:1"
#define SERIAL_BAUD_RATE 9600
#define WIFI_SSID "WiFi_ROUTER_SSID_HERE"
#define WIFI_PASS "WiFi_ROUTER_PASS_HERE"
#define SOFT_AP_SSID "AP_SSID_HERE"
#define SOFT_AP_PASS "AP_PASS_HERE"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <lwip/netif.h>
#include <lwip/napt.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(SERIAL_BAUD_RATE);

  Serial.println("....");
  Serial.println("WiFi Connecting");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi Failed");
      while(1) {
          delay(1000);
      }
  }
  Serial.println("WiFi Connected");
  
  Serial.println("Setting up AP");
  IPAddress localIp = IPAddress(172, 217, 28, 254);
  IPAddress subnet = IPAddress(255, 255, 255, 0);
  WiFi.softAPConfig(localIp, localIp, subnet);
  WiFi.softAP(SOFT_AP_SSID, SOFT_AP_PASS);
  Serial.println("AP setup is done");

  Serial.println("Setting up AP DNS");
  IPAddress dnsOne = WiFi.dnsIP(0);
  IPAddress dnsTwo = WiFi.dnsIP(1);
  Serial.println(dnsOne);
  Serial.println(dnsTwo);
  if(dnsOne.isV4()) {
    Serial.println("Updating AP DNS");
    ip4_addr a;
    a.addr = dnsOne.v4();
    WiFi.softAPDhcpServer().setDns(a);
  } else {
    Serial.println("AP DNS is not set!!!");
  }
  if(WiFi.softAPDhcpServer().isRunning()) {
    Serial.println("AP is running");
  } else {
    Serial.println("AP is not running!!!");
  }

  Serial.println("Setting up AP NAT for ipv4");
  err_t ret = ip_napt_init(IP_NAPT_MAX, IP_PORTMAP_MAX);
  if (ret == ERR_OK) {
    Serial.println("AP NAT initialization success");
    ret = ip_napt_enable_no(SOFTAP_IF, 1);
  } else {
    Serial.println("AP NAT init failed");
  }
  if (ret == ERR_OK) {
    Serial.println("AP NAT enabled");
  } else {
    Serial.println("AP NAT enabling failed");
  }

  /*
  // setup netif - not needed
  netif *a = WiFi.softAPDhcpServer().getNetif();
  netif_set_default_LWIP2(a);
  netif_set_ipaddr(a, localIp);
  netif_set_netmask(a, subnet);
  netif_set_gw(a, localIp);
  netif_set_default(a);
  */

  /*
  // set ipv6 static IP as link local
  ip6_addr ip6_addr = { 0 };
  ip6addr_aton(CONFIG_IPV6_STATIC_ADDR, &ip6_addr);
  netif_add_ip6_address(a, &ip6_addr, 0);
  netif_create_ip6_linklocal_address(a, 0);
  Serial.println("is netif up");
  Serial.println(netif_is_link_up(a));
  Serial.println(netif_is_up(a));
  */
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(30*1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
}
