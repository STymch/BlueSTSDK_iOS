/*******************************************************************************
 * COPYRIGHT(c) 2015 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#ifndef BlueSTSDK_BlueSTSDKNode_prv_h
#define BlueSTSDK_BlueSTSDKNode_prv_h

#include <CoreBluetooth/CBPeripheral.h>
#include <CoreBluetooth/CBCharacteristic.h>
#include "BlueSTSDKNode.h"

/**
 * package method of the {@link BlueSTSDKNode} class
 * @author STMicroelectronics - Central Labs.
 */
@interface BlueSTSDKNode(Prv)

/**
 *  create a new node, if the node doesn't has a correct advertise this method will
 * throw an exception
 *
 *  @param peripheral        ble peripheral that
 *  @param rssi              advertise rssi
 *  @param advertisementData data in the advertise
 *
 *  @return class BlueSTSDKNode
 *  @throw NSException if the ble advertise hasn't all the mandatory fields
 */
-(instancetype) init :(CBPeripheral *)peripheral rssi:(NSNumber*)rssi
  advertise:(NSDictionary*)advertisementData;

/**
 *  initialize the node without a peripheral
 * \note it will not be able to do anything this function is needed if you want
 * extend the node and keep using the delegate system build by this class
 *
 *  @return semi functional node pointer
 */
-(instancetype) init;

/**
 *  this method will update the rssi node value and notify the update to
 * the delegates
 *
 *  @param rssi new rssi values
 */
-(void)updateRssi:(NSNumber*)rssi;

/**
 *  this method will update the txPower of the node and notify the update to
 * the delegates
 *
 *  @param txPower new tx power
 */
-(void)updateTxPower:(NSNumber*)txPower;

/**
 *  this method is called by the BlueSTSDKManager when the CBCentralManager
 * complete the connection with the peripheral, this method will start to request
 * the node service and characteristics
 */
-(void)completeConnection;

/**
 *  this method is called by  BlueSTSDKManager when the CBCentralManager is not able
 *  to complete a connection because some error happen
 *
 *  @param error error occurred during the disconnection
 */
-(void)connectionError:(NSError*)error;

/**
 *  this method is called by the BlueSTSDKManager when the CBCentralManager complete the
 * peripheral disconnection.
 *
 *  @param error optional error occurred during the disconnection
 */
-(void)completeDisconnection:(NSError*)error;

/**
 *  change the node status and notify the event to the delegates
 *
 *  @param newState new node status
 */
-(void)updateNodeStatus:(BlueSTSDKNodeState)newState;

/**
 *  called by the CBPeripheralDelegate when a characteristics is read or notify
 *
 *  @param characteristics characteristics that has new data to be parsed
 */
-(void)characteristicUpdate:(CBCharacteristic*)characteristics;

/**
 *  send a command to the command service in the node
 *
 *  @param f           feature that will receive the command
 *  @param commandType command id
 *  @param commandData optional command data
 *
 *  @return true if the command is correctly send
 */
-(BOOL)sendCommandMessageToFeature:(BlueSTSDKFeature*)f type:(uint8_t)commandType
                              data:(NSData*) commandData;

/**
 *  write a data into a feature characteristics
 *
 *  @param f receiver feature
 *  @param data data to send to the feature
 *
 *  @return true if the command is correctly send
 */
-(BOOL)writeDataToFeature:(BlueSTSDKFeature*)f data:(NSData*)data;


@end


#endif
