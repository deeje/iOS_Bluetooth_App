//
//  BTBluetoothManager.h
//  bluetooth-demo
//
//  Created by John Bender on 9/26/13.
//  
//

#import <Foundation/Foundation.h>
#if USE_CAN
#import <AsyncNetwork/AsyncNetwork.h>
#else
#import <MultipeerConnectivity/MultipeerConnectivity.h>
#endif

typedef enum {
    BluetoothCommandHandshake=1,
    BluetoothCommandNegotiate,
    BluetoothCommandNegotiateConfirm,
    BluetoothCommandLayout,
    BluetoothCommandPickUp,
    BluetoothCommandMove,
    BluetoothCommandDrop
} BluetoothCommand;


#if USE_CAN
@interface BTBluetoothManager : NSObject <AsyncServerDelegate, AsyncClientDelegate>
#else
@interface BTBluetoothManager : NSObject <MCNearbyServiceBrowserDelegate, MCNearbyServiceAdvertiserDelegate, MCSessionDelegate>
#endif
{
#if USE_CAN
#else
    MCNearbyServiceBrowser *nearbyBrowser;
    MCNearbyServiceAdvertiser *nearbyAdvertiser;

    MCSession *session;
    NSString *peerId;
#endif
    
    NSDate *playerIndexTimestamp;
}

@property (nonatomic, readonly) NSString *peerName;
@property (nonatomic, readonly) NSInteger playerIndex;

#if USE_CAN
@property (strong, nonatomic)   AsyncServer                 *tcpServer;
@property (strong, nonatomic)   AsyncClient                 *tcpClient;
#endif

+(BTBluetoothManager*) instance;
+(BOOL) hasConnection;

-(void) sendDictionaryToPeers:(NSDictionary*)dict;

@end
