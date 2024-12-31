import asyncio
from bleak import BleakScanner, BleakClient

ODK_UUIDs = {"b23cca98-2545-4842-a5af-0fc3550aadb0":"odkService",
             "b23cca98-2545-4842-a5af-0fc3550aadb1":"battery",
             "b23cca98-2545-4842-a5af-0fc3550aadb2":"latitude", 
             "b23cca98-2545-4842-a5af-0fc3550aadb3":"longitude",
             "b23cca98-2545-4842-a5af-0fc3550aadb4":"time",
             "b23cca98-2545-4842-a5af-0fc3550aadb5":"date",
             "b23cca98-2545-4842-a5af-0fc3550aadb6":"anlg0",
             "b23cca98-2545-4842-a5af-0fc3550aadb7":"anlg1"}

def print_services_and_characteristics(services):
    print("\nServices and Characteristics:")
    for service in services:
        print(f"Service: {service.uuid}")
        for char in service.characteristics:
            print(f"  Characteristic: {char.uuid}")
            print(f"    Properties: {char.properties}")

async def read_characteristics(client, services):
    print("\nReading Readable Characteristics:")
    for service in services:
        for char in service.characteristics:
            if "read" in char.properties:
                try:
                    value = await client.read_gatt_char(char.uuid)
                    if char.uuid in ODK_UUIDs:
                        char_name = ODK_UUIDs[char.uuid]
                    else:
                        char_name = char.uuid
                    print(f"Characteristic {ODK_UUIDs[char.uuid]} value: {value}")
                except Exception as e:
                    print(f"Failed to read {char.uuid}: {e}")

async def main():
    print("Scanning for Bluetooth devices...")
    devices = await BleakScanner.discover()

    if not devices:
        print("No devices found. Exiting.")
        return

    print("Discovered devices:")
    choice = None
    for i, device in enumerate(devices):
        print(f"[{i}] {device.name} ({device.address})")
        if device.name == "ODK - Oasis Development Kit":
            print("Found ODK - Auto-Connecting...")
            choice = i
            break

    if choice == None:
        choice = input("Enter the number of the device to connect to: ")
        try:
            choice = int(choice)
            if choice < 0 or choice >= len(devices):
                raise ValueError("Invalid device selection.")
        except ValueError as e:
            print(f"Invalid input: {e}. Exiting.")
            return

    selected_device = devices[choice]
    print(f"Connecting to {selected_device.name} ({selected_device.address})...")

    async with BleakClient(selected_device.address) as client:
        if client.is_connected:
            print("Successfully connected!")
            services = await client.get_services()
            print_services_and_characteristics(services)
            await read_characteristics(client, services)
        else:
            print("Failed to connect to the device.")

if __name__ == "__main__":
    asyncio.run(main())
