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

#include <time.h>
#include <hidapi/hidapi.h>

// int send_clock(hid_device *dev)
// {
// 	time_t now = time(NULL);
// 	struct tm *t = localtime(&now);
//
// 	unsigned char report[65] = {0};
//
// 	report[0] = 0x04;    // Report ID
// 	report[1] = 0x20;    // Config command
// 	report[2] = 0x00;    // Reserved
// 	report[3] = 0x1A;    // RTC command
// 	report[4] = 0x06;    // 6-byte payload
//
// 	report[5] = (t->tm_year + 1900) % 100;  // YY
// 	report[6] = t->tm_mon + 1;              // MM
// 	report[7] = t->tm_mday;                 // DD
// 	report[8] = t->tm_hour;                 // HH
// 	report[9] = t->tm_min;                  // MM
// 	report[10] = t->tm_sec;                 // SS
//
// 	return hid_write(dev, report, sizeof(report));
// }

// static unsigned char bcd(unsigned int x)
// {
// 	return ((x / 10) << 4) | (x % 10);
// }

// report[5] = bcd((t->tm_year + 1900) % 100);
// report[6] = bcd(t->tm_mon + 1);
// report[7] = bcd(t->tm_mday);
// report[8] = bcd(t->tm_hour);
// report[9] = bcd(t->tm_min);
// report[10] = bcd(t->tm_sec);

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