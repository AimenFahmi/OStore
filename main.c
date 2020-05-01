#include <stdio.h>
#include "util/string_manipulation/StringManipulator.h"
#include "data/item/Item.h"
#include "data_structures/hashtable/Store_HashTable.h"
#include "util/sqlite3/Sqlite3_Manager.h"
#include "data/store/store.h"
#include "communication_protocol/CommunicationProtocol.h"
#include <sqlite3.h>
#include <time.h>

float newPrice() {
    int price = 6999;
    int variation = 5000;
    return (float) price-(rand()%10)*(variation/10.);
}

int main() {
    /*srand(time(0));
    sqlite3 *database = openDatabase("../util/sqlite3/Items.db");

    store_t *store = createStore();

    writeItemToStore(newItem("SCOTT SCALE RC 900 WORLD CUP AXS BIKE", rand()%100, newPrice(), "World Cup aspirations require a World Cup Quality ride. Lightweight, stiff, fast as- this is what you can expect from the Scale RC 900 World Cup. With SRAM's new AXS Wireless shifting and carbon wizardry, the World Cup can help you go from Nino Schurter super fan to perhaps putting on the leader's jersey. The bike can make it there, can you? Only time will tell.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274586_1586218_png_overview_4.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SCALE RC 900 PRO BIKE", rand()%100, newPrice(), "What is Pro? Is it one of the World's lightest Carbon frames? Is it top of the line componentry fit for racing at the world's highest level? Is it the confidence that a racing mastercraft brings out in a racer? Yes, that is pro. That and the Scale RC 900 Pro, your secret weapon for the season to come.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274588_1586221_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SCALE RC 900 TEAM BIKE", rand()%100, newPrice(), "With the SCOTT Scale RC Team, get yourself on the road to faster lap times. Designed to compete with the best, the Scale RC Team features a RockShox SID fork, a SRAM Eagle Drivetrain and Syncros components to deliver a package that is sure to make it's mark.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274589_1586222_png_overview_2.png", "Cross Country Bikes"), store);

    writeItemToStore(newItem("SCOTT SCALE 910 BIKE", rand()%100, newPrice(), "The SCOTT Scale 910 has geometry inspired by racing at the highest level, a Shimano XT 12-speed drivetrain and Syncros components combine to give you a hard tail that is just itching to finish first.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274590_1586224_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SCALE 925 BIKE", rand()%100, newPrice(), "The SCOTT Scale 925 has geometry inspired by racing at the highest level. A Shimano 12-speed drivetrain and Syncros components combine to give you a hard tail that is just itching to finish first.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274592_1586227_png_overview_4.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SCALE 930 BIKE", rand()%100, newPrice(), "The SCOTT Scale 930 boasts a super light Carbon Fiber frame. FOX suspension, a SRAM Eagle drivetrain and Syncros components combine to create a lightweight and efficient racing machine.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274593_1586228_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SCALE 940 BLACK/RED BIKE", rand()%100, newPrice(), "The SCOTT Scale 940 features an ultralight Carbon Frame. RockShox suspension, a SRAM Eagle drivetrain and Syncros components create a durable and affordable hardtail designed for world-class speed.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274595_1586231_png_overview_2.png", "Cross Country Bikes"), store);

    writeItemToStore(newItem("SCOTT SCALE 960 BIKE", rand()%100, newPrice(), "The SCOTT Scale 960 comes fully equipped with a Shimano 12-speed drivetrain and a RockShox fork, along with Remote Lockout technology to allow for multiple travel settings to adjust to riding conditions.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274604_1586243_png_overview_4.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SCALE 965 BIKE", rand()%100, newPrice(), "The SCOTT Scale 965 comes fully equipped with a Shimano 12-speed drivetrain and a RockShox fork, along with Remote Lockout technology to allow for multiple travel settings to adjust to riding conditions.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274605_1586244_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SCALE 970 BLACK/YELLOW BIKE", rand()%100, newPrice(), "The SCOTT Scale 970 comes fully equipped with a SRAM Eagle 12-speed drivetrain and a RockShox fork, along with Remote Lockout technology to allow for multiple travel settings to adjust to riding conditions.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274607_1586247_png_overview_4.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SCALE 980 BLACK/RED BIKE", rand()%100, newPrice(), "The SCOTT Scale 980 comes fully equipped with a SRAM Eagle 12-speed drivetrain and a Suntour fork, along with Remote Lockout technology to allow for multiple travel settings to adjust to riding conditions.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274608_1586248_png_overview_2.png", "Cross Country Bikes"), store);

    writeItemToStore(newItem("SCOTT SPARK RC 900 SL AXS BIKE", rand()%100, newPrice(), "Having already written itself into the history books, the Spark platform has been revamped, and is faster and fitter than ever. With the lightest frame in the RC series, the SL version comes equipped with a FOX 32 SC Fork, a SRAM Eagle AXS 12-speed wireless drivetrain, and a host of Syncros carbon components that will make any rider feel like they can go toe to toe with the world's finest.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274615_1586257_png_overview_4.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SPARK RC 900 WORLD CUP AXS BIKE", rand()%100, newPrice(), "The Spark RC 900 World Cup is a cross-country full-suspension bike on a mission to win. Keeping the ride smooth, a RockShox SID Ultimate fork is paired with a custom RockShox NUDE 3-mode rear shock via our TwinLoc Suspension System. The SRAM Eagle AXS 12-speed wireless drivetrain will move you up the trail and SRAM Level disc brakes will slow you down when it's time to step onto the podium.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274616_1586258_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SPARK RC 900 WORLD CUP BIKE", rand()%100, newPrice(), "The Spark RC 900 World Cup is a cross-country full-suspension bike on a mission to win. Keeping the ride smooth, a RockShox SID Select+ fork is paired with a custom RockShox NUDE 3-mode rear shock via our TwinLoc Suspension System. The SRAM X01 Eagle 12-speed drivetrain will move you up the trail and SRAM Level disc brakes will slow you down when it's time to step onto the podium.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274617_1586260_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SPARK RC 900 PRO BIKE", rand()%100, newPrice(), "Anyone who ever dreamed of a pro cross-country racing career has dreamed of the Spark RC 900 Pro. The 1x-specific Spark RC frame design and lightweight, hyper-efficient TwinLoc Suspension System are made for pure, on-course performance. The Pro build includes a Shimano XTR 12-speed drivetrain and XTR brakes, and is made to go the distance with premium Syncros components completing this race-worthy package in style.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274618_1586261_png_overview_2.png", "Cross Country Bikes"), store);

    writeItemToStore(newItem("SCOTT SPARK RC 900 TEAM ISSUE AXS BIKE", rand()%100, newPrice(), "With the Spark RC Team Issue AXS, take your World Championship dreams and start making them a reality. The fastest frame on the market, a wireless SRAM 12-speed groupset and Syncros components combine to give you the perfect tool for the job, whether you're racing a local weekend race or toeing it up for your first World Cup.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274619_1586262_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SPARK RC 900 TEAM RED BIKE", rand()%100, newPrice(), "The Spark 900 RC Team features a slew of high-end components in an affordable package. Our TwinLoc Suspension System, a 12-speed SRAM Eagle drivetrain, Shimano brakes and Syncros components combine to create a dreamworthy carbon full suspension race bike.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274620_1586263_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SPARK RC 900 TEAM GREEN BIKE", rand()%100, newPrice(), "The Spark 900 RC Team features a slew of high-end components in an affordable package. Our TwinLoc Suspension System, a 12-speed SRAM Eagle drivetrain, Shimano brakes and Syncros components combine to create a dreamworthy carbon full suspension race bike.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274621_1586265_png_overview_4.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT SPARK RC 900 COMP BIKE", rand()%100, newPrice(), "The Spark 900 RC Comp comes with a lightweight alloy frame that mimics its carbon siblings', and componentry that is fit for a pro. The rig features our TwinLoc Suspension System, a SRAM Eagle Groupset, Shimano brakes and Syncros components. Dropping the competition will become second nature.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274622_1586266_png_overview_2.png", "Cross Country Bikes"), store);

    writeItemToStore(newItem("SCOTT CONTESSA SCALE 910 BIKE", rand()%100, newPrice(), "The SCOTT Contessa Scale 910's HMF Carbon Fiber Frame packs one hell of a punch. The 910 comes fully equipped with a Shimano 12-speed drivetrain, and a FOX 32 Float fork, along with our RideLoc technology to allow for three travel settings to always optimize your ride. This bike is as race ready as it gets.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274782_1586424_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT CONTESSA SCALE 920 BIKE", rand()%100, newPrice(), "The SCOTT Contessa Scale 920's HMF Carbon Fiber Frame packs one hell of a punch. The 920 comes fully equipped with a SRAM Eagle drivetrain, and a FOX 32 Float fork, along with our RideLoc technology to allow for three travel settings to always optimize your ride. This bike is as race ready as it gets.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274783_1586425_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT CONTESSA SCALE 930 BIKE", rand()%100, newPrice(), "The SCOTT Contessa Scale 930's HMF Carbon Fiber Frame packs one hell of a punch. The 930 comes fully equipped with a SRAM Eagle drivetrain, and a RockShox fork. This bike is as race ready as it gets.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274784_1586426_png_overview_2.png", "Cross Country Bikes"), store);
    writeItemToStore(newItem("SCOTT CONTESSA SPARK RC 900 BIKE", rand()%100, newPrice(), "The Contessa Spark RC 900 is a cross-country full-suspension bike on a mission to win. Keeping the ride smooth, a RockShox SID Select + fork is paired with a custom RockShox NUDE 3-mode rear shock via our TwinLoc Suspension System. The SRAM X01 Eagle 12-speed drivetrain will move you up the trail and SRAM Level disc brakes will slow you down when it's time to step onto the podium.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274785_1586427_png_overview_4.png", "Cross Country Bikes"), store);

    writeItemToStore(newItem("SCOTT GAMBLER 900 TUNED BIKE", rand()%100, newPrice(), "The all NEW Gambler Tuned was designed for one thing and one thing only, pure, unadulterated speed. We made it to get you to take lines you'd never thought imaginable, to make you want to go to the bathroom before your race run - twice. We made it so that when you drop out of the start gate, the only aspect holding you back will be, well, you. Taking years of racing development and mixing it with our carbon expertise, this bike is our answer to the needs of white-knuckle downhill racing. The Gambler, Simply Fast.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274656_1586300_png_overview_4.png", "Downhill bikes"), store);
    writeItemToStore(newItem("SCOTT GAMBLER 910 BIKEv", rand()%100, newPrice(), "The all NEW Gambler was designed for one thing and one thing only, pure, unadulterated speed. We made it to get you to take lines you'd never thought imaginable, to make you want to go to the bathroom before your race run - twice. We made it so that when you drop out of the start gate, the only aspect holding you back will be, well, you. Taking years of racing development and mixing it with our carbon expertise, this bike is our answer to the needs of white-knuckle downhill racing. The Gambler, Simply Fast.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274657_1586301_png_overview_2.png", "Downhill bikes"), store);
    writeItemToStore(newItem("SCOTT GAMBLER 920 BIKE", rand()%100, newPrice(), "The all NEW Gambler was designed for one thing and one thing only, pure, unadulterated speed. We made it to get you to take lines you'd never thought imaginable, to make you want to go to the bathroom before your race run - twice. We made it so that when you drop out of the start gate, the only aspect holding you back will be, well, you. The Gambler 920 is the lightweight alloy DH bike of your dreams, and it too is simply fast.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274658_1586302_png_overview_4.png", "Downhill bikes"), store);
    writeItemToStore(newItem("SCOTT GAMBLER 930 BIKE", rand()%100, newPrice(), "The all NEW Gambler was designed for one thing and one thing only, pure, unadulterated speed. We made it to get you to take lines you'd never thought imaginable, to make you want to go to the bathroom before your race run - twice. We made it so that when you drop out of the start gate, the only aspect holding you back will be, well, you. The Gambler 930 is the lightweight alloy DH bike of your dreams, and it too is simply fast.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274659_1586303_png_overview_2.png", "Downhill bikes"), store);
    writeItemToStore(newItem("SCOTT VOLTAGE YZ 0.1 BIKE", rand()%100, newPrice(), "The SCOTT Voltage YZ 0.1 is our Pro riders replica bike built around a high-end Alloy dirtjump frame. Equipped with ultashort adjustable chain stays, a tapered headtube and high-end components, this bike is perfect for hitting the pumptrack, the dirtjumps, or jibbin' through the streets.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274660_1586304_png_overview_2.png", "Downhill bikes"), store);



    displayStore(store);

    dumpStoreToDatabase(database, store);
    displayDatabase(database);

    sqlite3_close_v2(database);*/

    /*item_t *data = newItem("SCOTT SCALE RC 900 WORLD CUP AXS BIKE", rand()%100, newPrice(), "World Cup aspirations require a World Cup Quality ride. Lightweight, stiff, fast as this is what you can expect from the Scale RC 900 World Cup. With SRAM's new AXS Wireless shifting and carbon wizardry, the World Cup can help you go from Nino Schurter super fan to perhaps putting on the leader's jersey. The bike can make it there, can you? Only time will tell.", "https://dfp2hfrf3mn0u.cloudfront.net/274/274586_1586218_png_overview_4.png", "Cross Country Bikes");
    char * item_as_string = convertItemToString(data);
    item_t *item_as_item = convertStringToItem(item_as_string);

    printf("%s", item_as_string);
    printItem(item_as_item);*/
    char buff1[10];
    char buff2[15];

    for (int i = 0; i < 5; ++i) {
        buff1[i] = 'a';
    }
    buff1[5] = '\0';

    for (int i = 0; i < 8; ++i) {
        buff2[i] = 'b';
    }
    buff2[8] = '\0';


    char *string = concat(buff1, buff2);

    printf("%s\n", string);

    return 0;
}