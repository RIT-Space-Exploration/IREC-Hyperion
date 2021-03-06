/**
 * File: IREC-Hyperion_Protocol.h
 * Organization: RIT Space Exploration
 * Description:
 *      Protocol to be used on the Hyperion payload.
 */

#ifndef IREC_HYPERION_PROTOCOL_LIBRARY_H
#define IREC_HYPERION_PROTOCOL_LIBRARY_H

#define BYTE_MASK 255
#define NIBBLE_MASK 15

#include <stdint.h>

// Size in Bytes
#define HEADER_SIZE 3
#define LSM9DS1_FRAME_SIZE 36
#define BME280_FRAME_SIZE 16
#define CCS811_FRAME_SIZE 4
#define LIS331_FRAME_SIZE 12
#define PFSL_FRAME_SIZE 4
#define OREN_FRAME_SIZE 4

/////////////////////
/// Data Structs ///
///////////////////

/**
 * Unpacked header
 */
typedef struct unpk_header{
    uint8_t data_type;
    uint8_t flags;
    uint16_t time;
} unpk_header;

/**
 * Data struct for the LSM8DS1 data frame
 */
typedef struct LSM9DS1_Data{
    int32_t ax, ay, az;
    int32_t gx, gy, gz;
    int32_t mx, my, mz;
} LSM9DS1_Data;

/**
 * Data struct for the BME280 data frame
 */
typedef struct BME280_Data{
    int32_t temperature;
    int32_t pressure;
    int32_t humidity;
    int32_t altitude;
} BME280_Data;

/**
 * Data struct for the CSS811 data frame
 */
typedef struct CCS811_Data{
    int16_t co2;
    int16_t TVOC;
} CCS811_Data;

/**
 * Data struct for the LIS311 data frame
 */
typedef struct LIS311_Data{
    int32_t ax, ay, az;
} LIS311_Data;

/**
 * Data struct for the PFSL data frame
 */
typedef struct PFSL_Data{
    int32_t alt;
} PFSL_Data;

/**
 * Data struct for the oren data frame
 */
typedef struct OREN_Data{
    int16_t pitch;
    int16_t roll;
    int16_t yaw;
} OREN_Data;

/**
 * Packet struct containing LSM9DS1 data and header.
 */
typedef struct LSM9DS1_Packet{
    unpk_header header;
    LSM9DS1_Data data;
} LSM9DS1_Packet;

/**
 * Packet struct containing BME280 data and header.
 */
typedef struct BME280_Packet{
    unpk_header header;
    BME280_Data data;
} BME280_Packet;

/**
 * Packet struct containing CCS811 data and header.
 */
typedef struct CCS811_Packet{
    unpk_header header;
    CCS811_Data data;
} CCS811_Packet;

/**
 * Packet struct containing LIS311 data and header.
 */
typedef struct LIS311_Packet{
    unpk_header header;
    LIS311_Data data;
} LIS311_Packet;

/**
 * Packet struct containing PFSL data and header.
 */
typedef struct PFSL_Packet{
    unpk_header header;
    PFSL_Data data;
} PFSL_Packet;

typedef struct OREN_Packet{
    unpk_header header;
    OREN_Data data;
} OREN_Packet;

typedef struct Info_Packet{
    unpk_header header;
    char data[300];
} Info_Packet;

/**
 * Packet used for commands/phase status
 */
typedef struct CMMND_Packet{
    unpk_header header;
} CMMND_Packet;

/**
 * Data Type Enums
 */
enum DataFrameType{
    NULLDATAt,
    LSM9DS1t,
    BME280t,
    CCS811t,
    LIS331t,
    PFSLt,
    Orent,
    CMMNDt,
    INFOt
};

// TODO add unpacking functionality
// TODO finish packing functions for all data groupss

/**
 * Main class for IREC-HYPERION_PROTOCOL
 */
class IRECHYPERP {
public:

    /**
     * Determines the type of data contained in buff
     * @param buff
     *      Packet data
     * @return
     *      A type corresponding to header data
     */
    static int typeofData(const uint8_t buff[]){
        return buff[0] >> 4;
    }

    /**
     * Main packer function for the LSMDS1 data frame.
     * @param flags
     *      Header flags
     * @param time
     *      Time in seconds
     * @param ax
     *      Acceleration value on the X axis
     * @param ay
     *      Acceleration value on the Y axis
     * @param az
     *      Acceleration value on the Z axis
     * @param gx
     *      Gyroscope value on the X axis
     * @param gy
     *      Gyroscope value on the Y axis
     * @param gz
     *      Gyroscope value on the Z axis
     * @param mx
     *      Magnetic value on the X axis
     * @param my
     *      Magnetic value on the Y axis
     * @param mz
     *      Magnetic value on the Z axis
     * @return
     *      A fully complete data frame with header
     */
    static void createLSM9DS1Frame(uint8_t buff[], char *flags, uint16_t time,
                       int32_t ax, int32_t ay, int32_t az,
                       int32_t gx, int32_t gy, int32_t gz,
                       int32_t mx, int32_t my, int32_t mz);

    /**
     * Main packer function for the BME280 data frame
     * @param flags
     *      Header flags
     * @param time
     *      Time in seconds (Epoch)
     * @param temp
     *      Temperature in C
     * @param humidity
     *      Humidity in percentage
     * @param pressure
     *      Pressure
     * @param altitude
     *      Altitude in m
     * @return
     *      A fully complete data frame with header
     */
    static void createBME280Frame(uint8_t buff[], char flags[], uint16_t time,
                                   int32_t temp, int32_t humidity, int32_t pressure, int32_t altitude);

    /**
     * Main packer function for the CCS811 data frame.
     * @param flags
     *      Header flags
     * @param time
     *      Time in seconds (Epoch)
     * @param co2
     *      CO2 in ppm
     * @param TVOC
     *      TVOC in ppm
     * @return
     *      A fully complete data frame with header
     */
    static void createCCS811Frame(uint8_t buff[], char flags[], uint16_t time,
                                   int16_t co2, int16_t TVOC);
    /**
     * Main packer function for the LIS311 data frame.
     * @param flags
     *      Header flags
     * @param time
     *      Time in seconds (Epoch)
     * @param ax
     *      Acceleration value on the X axis
     * @param ay
     *      Acceleration value on the Y axis
     * @param az
     *      Acceleration value on the Z axis
     * @return
     *      A fully complete data frame with header
     */
    static void createLIS311Frame(uint8_t buff[], char flags[], uint16_t time,
                                   int32_t ax, int32_t ay, int32_t az);

    /**
     * Main packer function for the PFSL data frame
     * @param buff
     * @param flags
     * @param time
     * @param altitude
     */
    static void createPFSLFrame(uint8_t buff[], char flags[], uint16_t time, int32_t altitude);

    /**
     * Main packer function for the orentation data frame
     * @param buff
     * @param flags
     * @param time
     * @param pitch
     * @param roll
     * @param yaw
     */
    static void createOrenFrame(uint8_t buff[], char flags[], uint16_t time, int32_t pitch, int32_t roll, int32_t yaw);

    /**
     * Main packer function for the command frame
     * @param buff
     * @param flags
     * @param time
     */
    static void createCMMNDFrame(uint8_t buff[], char flags[], uint16_t time);

    /**
     * Main packer function for a info frame
     * @param buff
     * @param flags
     * @param time
     * @pram msg
     */
    static void createInfoFrame(uint8_t buff[], char flags[], uint16_t time, char msg[]);

    /**
     * Unpack function for the LSM9DS1 data frame
     * @param buff
     *      A array containing a packed LSM9DS1 packet
     * @return
     *      A LSM9DS1 packet
     */
    static LSM9DS1_Packet unpack_LSM9DS1(const uint8_t buff[]);

    /**
     * Unpack function for the BME280 packet
     * @param buff
     *      A array containing a packed BME280 packet
     * @return
     *      A BME280 packet
     */
    static BME280_Packet unpack_BME280(const uint8_t buff[]);

    /**
     * Unpack function for the CCS811 packet
     * @param buff
     *      A array containing a packed CCS811 packet
     * @return
     *      A CCS811 packet
     */
    static CCS811_Packet unpack_CCS811(const uint8_t buff[]);

    /**
     * Unpack function for the LIS311 packet
     * @param buff
     *      A array containing a packed LIS311 packet
     * @return
     *      A LIS311 packet
     */
    static LIS311_Packet unpack_LIS311(const uint8_t buff[]);

    /**
     * Unpack function for the PFSL packet.
     * @param buff
     * @return
     */
    static PFSL_Packet unpack_PFSL(const uint8_t buff[]);

    /**
     * Unpack function for the oren data frame
     * @param buff
     * @return
     */
    static OREN_Packet unpack_Oren(const uint8_t buff[]);

    /**
     * Unpack function for the CMMND data frame
     * @param buff
     * @return
     */
    static CMMND_Packet unpack_CMMND(const uint8_t buff[]);

    /**
     * Unpack function for the Info data frame
     */
    static Info_Packet unpack_Info(const uint8_t buff[]);

private:
    /**
     * Creates a header using the provided values below.
     * @param type
     *      Type of data frame
     * @param flags
     *      Flags passes as an array
     * @param time
     *      Time in seconds
     * @return
     *      A null terminated string
     */
    static void createHeader(uint8_t buff[], DataFrameType type, const char *flags, uint16_t time);

    /**
     * Unpacks function for a hyperion header.
     * @param buff
     *      Array of header data values
     * @return
     *      A packed header struct
     */
    static unpk_header unpack_header(const uint8_t buff[]);

    /**
     * Unpack function for the LSM9DS1 data segment
     * @param buff
     *      Array of LSM9DS1 data values
     * @return
     *      A packed LSM9DS1 Data struct
     */
    static LSM9DS1_Data unpack_LSM9DS1_Data(const uint8_t buff[]);

    /**
     * Unpack function for the BME280 data segment
     * @param buff
     *      Array of BME280 data values
     * @return
     *      A packed BME280 Data struct
     */
    static BME280_Data unpack_BME280_Data(const uint8_t buff[]);

    /**
     * Unpack function for the CCS811 data segment
     * @param buff
     *      Array of CCS811 data values
     * @return
     *      A packed CCS811 Data struct
     */
    static CCS811_Data unpack_CCS811_Data(const uint8_t buff[]);

    /**
     * Unpack function for the LIS311 data segment
     * @param buff
     *      Array of LIS311 data values
     * @return
     *      A packed CCS811 Data struct
     */
    static LIS311_Data unpack_LIS311_Data(const uint8_t buff[]);

    /**
     * Unpack function for the PFSL data segment
     * @param buff
     * @return
     */
    static PFSL_Data unpack_PFSL_Data(const uint8_t buff[]);

    /**
     * Unpack function for the oren data frame
     * @param buff
     * @return
     */
    static OREN_Data unpack_Oren_Data(const uint8_t buff[]);
};
#endif
