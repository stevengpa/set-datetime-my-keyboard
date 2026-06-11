#include <stdio.h>
#include <string.h>
#include <hidapi/hidapi.h>

/*

IMPORTANT: Work In Progress

sudo dnf install hid-tools

pip install hid-tools

which hid-recorder
sudo ~/.pyenv/shims/hid-recorder

gcc datetime-keyboard.c -o datetime-keyboard -lhidapi-hidraw && sudo ./datetime-keyboard

*/
int main(void)
{

	hid_init();

    hid_device *dev =
        hid_open_path("/dev/hidraw7");

    if (!dev) {
        printf("open failed\n");
        return 1;
    }

    unsigned char buf[65];
    memset(buf, 0, sizeof(buf));

    buf[0] = 4;  // Report ID
	buf[1] = 0x10;
	buf[2] = 0x26;
	buf[3] = 0x06;
	buf[4] = 0x10;

    int r = hid_write(dev, buf, 65);

    printf("write result: %d\n", r);

    hid_close(dev);
    hid_exit();

    return 0;
}

// if (hid_init() != 0) {
	// 	printf("hid_init failed\n");
	// 	return 1;
	// }


	// struct hid_device_info *devs = hid_enumerate(0x320f, 0x511b);
	// struct hid_device_info *cur = devs;

	// printf("=== MY DEVICES ===\n");

	// while (cur) {
	//     printf("PATH: %s\n", cur->path);
	//     printf("INTERFACE: %d\n", cur->interface_number);
	//     printf("PRODUCT: %ls\n", cur->product_string ? cur->product_string : L"(null)");
	//     printf("------------------------\n");

	//     cur = cur->next;
	// }

	// hid_free_enumeration(devs);

	// const char *paths[] = {
    //     "/dev/hidraw6",
    //     "/dev/hidraw7",
    //     "/dev/hidraw8"
    // };

    // for (int i = 0; i < 3; i++) {
    //     try_device(paths[i]);
    // }


	// hid_device *dev = hid_open(0x320f, 0x511b, NULL);

	// if (!dev) {
	// 	puts("cannot open keyboard");
	// 	return 1;
	// }

	// unsigned char report[64] = {0};

	// report[0] = 4; // Report ID

	// Send Report
	// int rc = hid_send_feature_report(
	// 	dev,
	// 	report,
	// 	sizeof(report)
	// );

	// printf("rc=%d\n", rc);

	// Read Report
	// int rc = hid_get_feature_report(
    //     dev,
    //     report,
    //     sizeof(report)
    // );

	// for (int i = 0; i < rc; i++)
    // 	printf("%02X ", report[i]);

	// printf("\n");

	// hid_close(dev);
	// hid_exit();