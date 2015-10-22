#ifndef STICK20_COMMANDS_H
#define STICK20_COMMANDS_H
#include "inttypes.h"

namespace nitrokey {
namespace proto {

/*
*	STICK20 protocol command ids
*	a superset of STICK10
*/
namespace stick20 {
		class EnableEncryptedPartition : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30]; // TODO check w/ firmware
			};

			typedef Transaction<CommandID::ENABLE_CRYPTED_PARI,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class DisableEncryptedPartition : semantics::non_constructible {
		public:
			typedef Transaction<CommandID::DISABLE_CRYPTED_PARI,
									struct EmptyPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class EnableHiddenEncryptedPartition : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30]; // TODO check w/ firmware
			};

			typedef Transaction<CommandID::ENABLE_HIDDEN_CRYPTED_PARI,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class DisableHiddenEncryptedPartition : semantics::non_constructible {
		public:
			typedef Transaction<CommandID::DISABLE_CRYPTED_PARI,
									struct EmptyPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class EnableFirmwareUpdate : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30]; // TODO check w/ firmware
			};

			typedef Transaction<CommandID::ENABLE_FIRMWARE_UPDATE,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class UpdatePassword : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t old_password[15];
				uint8_t new_password[15];
			};

			typedef Transaction<CommandID::CHANGE_UPDATE_PIN,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class ExportFirmware : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30];
			};

			typedef Transaction<CommandID::EXPORT_FIRMWARE_TO_FILE,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class CreateNewKeys : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30];
			};

			typedef Transaction<CommandID::GENERATE_NEW_KEYS,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class FillSDCardWithRandomChars : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t volume_flag;
				uint8_t password[30];
			};

			typedef Transaction<CommandID::FILL_SD_CARD_WITH_RANDOM_CHARS,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class SetupHiddenVolume : semantics::non_constructible {
		public:
			typedef Transaction<CommandID::SEND_HIDDEN_VOLUME_SETUP,
									struct EmptyPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class SendPasswordMatrix : semantics::non_constructible {
		public:
			typedef Transaction<CommandID::SEND_PASSWORD_MATRIX,
									struct EmptyPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class SendPasswordMatrixPinData : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t pin_data[30]; // TODO how long actually can it be?
			};

			typedef Transaction<CommandID::SEND_PASSWORD_MATRIX_PINDATA,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class SendPasswordMatrixSetup : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t setup_data[30]; // TODO how long actually can it be?
			};

			typedef Transaction<CommandID::SEND_PASSWORD_MATRIX_SETUP,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class GetDeviceStatus : semantics::non_constructible {
		public:
			typedef Transaction<CommandID::GET_DEVICE_STATUS,
									struct EmptyPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class SendPassword : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30];
			};

			typedef Transaction<CommandID::SEND_PASSWORD,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class SendNewPassword : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30];
			};

			typedef Transaction<CommandID::SEND_NEW_PASSWORD,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		// TODO fix original nomenclature
		class SendSetReadonlyToUncryptedVolume : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30];
			};

			typedef Transaction<CommandID::ENABLE_READWRITE_UNCRYPTED_LUN,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class SendSetReadwriteToUncryptedVolume : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30];
			};

			typedef Transaction<CommandID::ENABLE_READWRITE_UNCRYPTED_LUN,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class SendClearNewSdCardFound : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30];
			};

			typedef Transaction<CommandID::CLEAR_NEW_SD_CARD_FOUND,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class SendStartup : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint64_t localtime; // POSIX
			};

			typedef Transaction<CommandID::SEND_STARTUP,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class SendHiddenVolumeSetup : semantics::non_constructible {
		public:
			struct CommandPayload {
				// TODO HiddenVolumeSetup_tst type
			};

			typedef Transaction<CommandID::SEND_HIDDEN_VOLUME_SETUP,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class LockFirmware : semantics::non_constructible {
		public:
			struct CommandPayload {
				uint8_t password[30];
			};

			typedef Transaction<CommandID::SEND_LOCK_STICK_HARDWARE,
									struct CommandPayload,
									struct EmptyPayload> CommandTransaction;
		};

		class ProductionTest : semantics::non_constructible {
		public:
			typedef Transaction<CommandID::PRODUCTION_TEST,
									struct EmptyPayload,
									struct EmptyPayload> CommandTransaction;
		};

}
}
}

#endif