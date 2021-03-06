#ifndef LIBNITROKEY_NK_C_API_H
#define LIBNITROKEY_NK_C_API_H

#include <iostream>
#include <string>
#include "include/NitrokeyManager.h"
#include "include/inttypes.h"

extern "C"
{
/**
 * Set debug level of messages written on stderr
 * @param state state=True - all messages, state=False - only errors level
 */
extern void NK_set_debug(bool state);

/**
 * Connect to device of given model. Currently library can be connected only to one device at once.
 * @param device_model char 'S': Nitrokey Storage, 'P': Nitrokey Pro
 * @return 1 if connected, 0 if wrong model or cannot connect
 */
extern int NK_login(const char *device_model);

/**
 * Connect to first available device, starting checking from Pro 1st to Storage 2nd.
 * @return 1 if connected, 0 if wrong model or cannot connect
 */
extern int NK_login_auto();

/**
 * Disconnect from the device.
 * @return command processing error code
 */
extern int NK_logout();

/**
 * Return the debug status string. Debug purposes.
 * @return command processing error code
 */
extern const char * NK_status();

/**
 * Return the device's serial number string in hex.
 * @return string device's serial number in hex
 */
extern const char * NK_device_serial_number();

/**
 * Get last command processing status. Useful for commands which returns the results of their own and could not return
 * an error code.
 * @return previous command processing error code
 */
extern uint8_t NK_get_last_command_status();

/**
 * Lock device - cancel any user device unlocking.
 * @return command processing error code
 */
extern int NK_lock_device();

/**
 * Authenticates the user on USER privilages with user_password and sets user's temporary password on device to user_temporary_password.
 * @param user_password char[25](Pro) current user password
 * @param user_temporary_password char[25](Pro) user temporary password to be set on device for further communication (authentication command)
 * @return command processing error code
 */
extern int NK_user_authenticate(const char* user_password, const char* user_temporary_password);

/**
 * Authenticates the user on ADMIN privilages with admin_password and sets user's temporary password on device to admin_temporary_password.
 * @param admin_password char[25](Pro) current administrator PIN
 * @param admin_temporary_password char[25](Pro) admin temporary password to be set on device for further communication (authentication command)
 * @return command processing error code
 */
extern int NK_first_authenticate(const char* admin_password, const char* admin_temporary_password);

/**
 * Execute a factory reset.
 * @param admin_password char[20](Pro) current administrator PIN
 * @return command processing error code
 */
extern int NK_factory_reset(const char* admin_password);

/**
 * Generates AES key on the device
 * @param admin_password char[20](Pro) current administrator PIN
 * @return command processing error code
 */
extern int NK_build_aes_key(const char* admin_password);

/**
 * Unlock user PIN locked after 3 incorrect codes tries.
 * @param admin_password char[20](Pro) current administrator PIN
 * @return command processing error code
 */
extern int NK_unlock_user_password(const char *admin_password, const char *new_user_password);

/**
 * Write general config to the device
 * @param numlock set value in range [0-1] to send HOTP code from slot 'numlock' after double pressing numlock
 * or outside the range to disable this function
 * @param capslock similar to numlock but with capslock
 * @param scrolllock similar to numlock but with scrolllock
 * @param enable_user_password set True to enable OTP PIN protection (request PIN each OTP code request)
 * @param delete_user_password set True to disable OTP PIN protection (request PIN each OTP code request)
 * @param admin_temporary_password current admin temporary password
 * @return command processing error code
 */
extern int NK_write_config(uint8_t numlock, uint8_t capslock, uint8_t scrolllock,
                           bool enable_user_password, bool delete_user_password, const char *admin_temporary_password);

/**
 * Get currently set config - status of function Numlock/Capslock/Scrollock OTP sending and is enabled PIN protected OTP
 * @see NK_write_config
 * @return  uint8_t general_config[5]:
 *            uint8_t numlock;
              uint8_t capslock;
              uint8_t scrolllock;
              uint8_t enable_user_password;
              uint8_t delete_user_password;

 */
extern uint8_t* NK_read_config();

//OTP

/**
 * Get name of given TOTP slot
 * @param slot_number TOTP slot number, slot_number<15
 * @return char[20](Pro) the name of the slot
 */
extern const char * NK_get_totp_slot_name(uint8_t slot_number);

/**
 *
 * @param slot_number HOTP slot number, slot_number<3
 * @return char[20](Pro) the name of the slot
 */
extern const char * NK_get_hotp_slot_name(uint8_t slot_number);

/**
 * Erase HOTP slot data from the device
 * @param slot_number HOTP slot number, slot_number<3
 * @param temporary_password admin temporary password
 * @return command processing error code
 */
extern int NK_erase_hotp_slot(uint8_t slot_number, const char *temporary_password);

/**
 * Erase TOTP slot data from the device
 * @param slot_number TOTP slot number, slot_number<15
 * @param temporary_password admin temporary password
 * @return command processing error code
 */
extern int NK_erase_totp_slot(uint8_t slot_number, const char *temporary_password);

/**
 * Write HOTP slot data to the device
 * @param slot_number HOTP slot number, slot_number<3
 * @param slot_name char[15](Pro) desired slot name
 * @param secret char[20](Pro) 160-bit secret
 * @param hotp_counter uint32_t starting value of HOTP counter
 * @param use_8_digits should returned codes be 6 (false) or 8 digits (true)
 * @param use_enter press ENTER key after sending OTP code using double-pressed scroll/num/capslock
 * @param use_tokenID @see token_ID
 * @param token_ID @see https://openauthentication.org/token-specs/, 'Class A' section
 * @param temporary_password char[25](Pro) admin temporary password
 * @return command processing error code
 */
extern int NK_write_hotp_slot(uint8_t slot_number, const char *slot_name, const char *secret, uint8_t hotp_counter,
                              bool use_8_digits, bool use_enter, bool use_tokenID, const char *token_ID,
                              const char *temporary_password);

/**
 * Write TOTP slot data to the device
 * @param slot_number TOTP slot number, slot_number<15
 * @param slot_name char[15](Pro) desired slot name
 * @param secret char[20](Pro) 160-bit secret
 * @param time_window uint16_t time window for this TOTP
 * @param use_8_digits should returned codes be 6 (false) or 8 digits (true)
 * @param use_enter press ENTER key after sending OTP code using double-pressed scroll/num/capslock
 * @param use_tokenID @see token_ID
 * @param token_ID @see https://openauthentication.org/token-specs/, 'Class A' section
 * @param temporary_password char[20](Pro) admin temporary password
 * @return command processing error code
 */
extern int NK_write_totp_slot(uint8_t slot_number, const char *slot_name, const char *secret, uint16_t time_window,
                              bool use_8_digits, bool use_enter, bool use_tokenID, const char *token_ID,
                              const char *temporary_password);

/**
 * Get HOTP code from the device
 * @param slot_number HOTP slot number, slot_number<3
 * @return HOTP code
 */
extern uint32_t NK_get_hotp_code(uint8_t slot_number);

/**
 * Get HOTP code from the device (PIN protected)
 * @param slot_number HOTP slot number, slot_number<3
 * @param user_temporary_password char[25](Pro) user temporary password if PIN protected OTP codes are enabled,
 * otherwise should be set to empty string - ''
 * @return HOTP code
 */
extern uint32_t NK_get_hotp_code_PIN(uint8_t slot_number, const char* user_temporary_password);

/**
 * Get TOTP code from the device
 * @param slot_number TOTP slot number, slot_number<15
 * @param challenge TOTP challenge
 * @param last_totp_time last time
 * @param last_interval last interval
 * @return TOTP code
 */
extern uint32_t NK_get_totp_code(uint8_t slot_number, uint64_t challenge, uint64_t last_totp_time, uint8_t last_interval);

/**
 * Get TOTP code from the device (PIN protected)
 * @param slot_number TOTP slot number, slot_number<15
 * @param challenge TOTP challenge
 * @param last_totp_time last time
 * @param last_interval last interval
 * @param user_temporary_password char[25](Pro) user temporary password if PIN protected OTP codes are enabled,
 * otherwise should be set to empty string - ''
 * @return TOTP code
 */
extern uint32_t NK_get_totp_code_PIN(uint8_t slot_number, uint64_t challenge,
                                     uint64_t last_totp_time, uint8_t last_interval, const char* user_temporary_password);

/**
 * Set time on the device (for TOTP requests)
 * @param time seconds in unix epoch (from 01.01.1970)
 * @return command processing error code
 */
extern int NK_totp_set_time(uint64_t time);

extern int NK_totp_get_time();
//passwords
/**
 * Change administrator PIN
 * @param current_PIN char[25](Pro) current PIN
 * @param new_PIN char[25](Pro) new PIN
 * @return command processing error code
 */
extern int NK_change_admin_PIN(char *current_PIN, char *new_PIN);

/**
 * Change user PIN
 * @param current_PIN char[25](Pro) current PIN
 * @param new_PIN char[25](Pro) new PIN
 * @return command processing error code
*/
extern int NK_change_user_PIN(char *current_PIN, char *new_PIN);


/**
 * Get retry count of user PIN
 * @return user PIN retry count
 */
extern uint8_t NK_get_user_retry_count();

/**
 * Get retry count of admin PIN
 * @return admin PIN retry count
 */
extern uint8_t NK_get_admin_retry_count();
//password safe

/**
 * Enable password safe access
 * @param user_pin char[30](Pro) current user PIN
 * @return command processing error code
 */
extern int NK_enable_password_safe(const char *user_pin);

/**
 * Get password safe slots' status
 * @return uint8_t[16] slot statuses - each byte represents one slot with 0 (not programmed) and 1 (programmed)
 */
extern uint8_t * NK_get_password_safe_slot_status();

/**
 * Get password safe slot name
 * @param slot_number password safe slot number, slot_number<16
 * @return slot name
 */
extern const char *NK_get_password_safe_slot_name(uint8_t slot_number);

/**
 * Get password safe slot login
 * @param slot_number password safe slot number, slot_number<16
 * @return login from the PWS slot
 */
extern const char *NK_get_password_safe_slot_login(uint8_t slot_number);

/**
 * Get the password safe slot password
 * @param slot_number password safe slot number, slot_number<16
 * @return password from the PWS slot
 */
extern const char *NK_get_password_safe_slot_password(uint8_t slot_number);

/**
 * Write password safe data to the slot
 * @param slot_number password safe slot number, slot_number<16
 * @param slot_name char[11](Pro) name of the slot
 * @param slot_login char[32](Pro) login string
 * @param slot_password char[20](Pro) password string
 * @return command processing error code
 */
extern int NK_write_password_safe_slot(uint8_t slot_number, const char *slot_name,
                                       const char *slot_login, const char *slot_password);

/**
 * Erase the password safe slot from the device
 * @param slot_number password safe slot number, slot_number<16
 * @return command processing error code
 */
extern int NK_erase_password_safe_slot(uint8_t slot_number);

/**
 * Check whether AES is supported by the device
 * @return 0 for no and 1 for yes
 */
extern int NK_is_AES_supported(const char *user_password);

}


#endif //LIBNITROKEY_NK_C_API_H
