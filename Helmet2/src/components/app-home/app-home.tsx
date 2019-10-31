import { Component, State, h } from "@stencil/core";
import { set } from "../../services/storage";

import { BLE } from '@ionic-native/ble';

@Component({
  tag: "app-home",
  styleUrl: "app-home.css"
})
export class AppHome {
  @State() testValue: string;

  @State() isConnected: boolean = false;
  @State() service: string = '';
  @State() characteristic: string = '';
  @State() deviceId: string = '75B764C2-B608-8BB8-5AEC-FCF9CE689B1B';

  @State() devices: any[] = [];

  stringToBytes(string) {
    var array = new Uint8Array(string.length);

    for (var i = 0, l = string.length; i < l; i++) {
      array[i] = string.charCodeAt(i);
    }

    return array.buffer;
  }

  sendToggle() {
    BLE.writeWithoutResponse(this.deviceId, this.service, this.characteristic, this.stringToBytes('V'));
  }

  sendFace(face: string = '') {
    BLE.writeWithoutResponse(this.deviceId, this.service, this.characteristic, this.stringToBytes('F' + face));
  }
  
  ble: any;

  constructor() {
    console.log('constrcutor');
    // this.ble = cordova.ble;
    //this.ble = BLE;
  }

  componentDidLoad() {
    console.error('Component did load');

    console.error("Start Scan");
  
    console.error(BLE);

    try {

      this.devices = [];

      BLE.scan([], 10).subscribe(
        device => {
          console.error("Got device");
          console.error(device);

          if (device.name === 'H') {
            this.devices = [...this.devices, device];
          }
        }, 
        error => {
          console.error('SCan error');
          console.error(error);
        }
      )
      
    } catch(e) {
      console.error("Could not scan");
      console.error(e);
    }    
  }

  connect(device: any) {
    console.log('connecting to device?');

    this.deviceId = device.id;

    BLE.autoConnect(this.deviceId, () => {
      console.error('COnnected?');
      this.isConnected = true;

      this.service = '713D0000-503E-4C75-BA94-3148F18D941E';
      this.characteristic = '713D0003-503E-4C75-BA94-3148F18D941E';

      console.error(this.deviceId);
      console.error(this.service);
      console.error(this.characteristic);

      /*setTimeout(() => {
        console.error('Trying to send');
        // BLE.writeWithoutResponse(this.deviceId, this.service, this.characteristic, this.stringToBytes('V'));
      }, 5000)*/
    }, (error) => {
      console.error(error);
    })
  }

  changeValue(value) {
    this.testValue = value;
    set("myValue", this.testValue);
  }

  clickDevice(device: any) {
    // this.ble.stopScan(); // TODO: this one

    this.connect(device);
    console.log('Clicked device' + device.id);
  }

  renderDevicesList() {
    console.error('Attmepting to render devices');
    return this.devices.map((device) => {
      console.log(device);

      return (
        <ion-item onClick={ () => { this.clickDevice(device) } }>
          <ion-label>{ device.name }</ion-label>
        </ion-item>
      )
    })
  }

  renderDevices() {
    return (
      <div>
        <h1>Devices</h1>

        { this.renderDevicesList() }
      </div>
    )
  }

  renderConnected() {
    return (
      <div>
        <h1>Lets do this:</h1>  
        
        <ion-button onClick={ () => { this.sendFace('A') } }>Blinking Eyes</ion-button>
        <ion-button onClick={ () => { this.sendFace('J') } }>Wink</ion-button>
        <ion-button onClick={ () => { this.sendFace('B') } }>Heart Face</ion-button>
        <ion-button onClick={ () => { this.sendFace('C') } }>Scanner</ion-button>
        <ion-button onClick={ () => { this.sendFace('D') } }>CMD</ion-button>
        <ion-button onClick={ () => { this.sendFace('E') } }>Apple</ion-button>
        <ion-button onClick={ () => { this.sendFace('F') } }>Heart Rate</ion-button>
        <ion-button onClick={ () => { this.sendFace('G') } }>Red EYe</ion-button>
        <ion-button onClick={ () => { this.sendFace('H') } }>Fasion</ion-button>
        <ion-button onClick={ () => { this.sendFace('I') } }>Party</ion-button>
        <ion-button onClick={ () => { this.sendFace('K') } }>Dang</ion-button>
        <ion-button onClick={ () => { this.sendFace('L') } }>Z</ion-button>
        <ion-button onClick={ () => { this.sendFace('N') } }>Blushing</ion-button>
      </div>
    );
  }

  render() {
    return [
      <ion-header>
        <ion-toolbar color="primary">
          <ion-title>Home</ion-title>
        </ion-toolbar>
      </ion-header>,

      <ion-content class="ion-padding">
        { this.devices.length }
        
        { this.isConnected ? this.renderConnected() : this.renderDevices() }
      </ion-content>
    ];
  }
}
