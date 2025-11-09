#include <cstring>
#include <iostream>
#include <libssh/libssh.h>

// Function to execute a command on the remote server
std::string executeRemoteCommand(ssh_session session, const std::string& command) {
    ssh_channel channel;
    int rc;
    char buffer[256];
    int nbytes;
    std::string result;

    channel = ssh_channel_new(session);
    if (channel == nullptr) {
        std::cerr << "Error creating SSH channel." << std::endl;
        return "";
    }

    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) {
        ssh_channel_free(channel);
        std::cerr << "Error opening SSH session: " << ssh_get_error(session)
                  << std::endl;
        return "";
    }

    rc = ssh_channel_request_exec(channel, command.c_str());
    if (rc != SSH_OK) {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        std::cerr << "Error executing command: " << ssh_get_error(session)
                  << std::endl;
        return "";
    }

    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0) {
        result.append(buffer, nbytes);
    }

    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);

    return result;
}

int ssh_auth(int rc, ssh_session session, const char* username,
             const char* password) {
    rc = ssh_userauth_password(session, nullptr, password);
    if (rc != SSH_AUTH_SUCCESS) {
        std::cerr << "Authentication failed: " << ssh_get_error(session)
                  << std::endl;
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }
    return rc;
}

int main(int argc, char** argv) {
    ssh_session my_ssh_session;
    int rc;
    const char* hostname = argv[1];

    const char* username = argv[2];
    const char* password = argv[3];

    // Create a new SSH session
    my_ssh_session = ssh_new();
    if (my_ssh_session == nullptr) {
        std::cerr << "Error creating SSH session." << std::endl;
        return EXIT_FAILURE;
    }

    // Set SSH options
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, hostname);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, username);

    // Connect to the server
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK) {
        std::cerr << "Error connecting to host: " << ssh_get_error(my_ssh_session)
                  << std::endl;
        ssh_free(my_ssh_session);
        return EXIT_FAILURE;
    }

    rc = ssh_auth(rc, my_ssh_session, username, password);

    std::string product_name_info = executeRemoteCommand(
        my_ssh_session, "cat /sys/devices/virtual/dmi/id/product_name");
    std::string product_family_info = executeRemoteCommand(
        my_ssh_session, "cat /sys/devices/virtual/dmi/id/product_family");
    std::string cpu_info = executeRemoteCommand(
        my_ssh_session, "cat /proc/cpuinfo | grep 'model name' | head -n 1 | "
                        "awk -F ': ' '{print $2}'");
    std::string mem_total_info = executeRemoteCommand(
        my_ssh_session,
        "cat /proc/meminfo | grep 'MemTotal' | awk '{print $(NF-1), $NF}'");
    std::string mem_free_info = executeRemoteCommand(
        my_ssh_session,
        "cat /proc/meminfo | grep 'MemFree' | awk '{print $(NF-1), $NF}'");
    std::string os_info = executeRemoteCommand(
        my_ssh_session, "cat /etc/*-release | grep NAME | head -n 1 | awk -F "
                        "'=' '{print $2}' | tr -d '\"' ");
    std::string vendor_info =
        executeRemoteCommand(my_ssh_session, "cat /sys/class/dmi/id/sys_vendor");

    // Display the retrieved information
    std::cout << "Product Name:\t"
              << product_name_info.erase(product_name_info.find('\n'), 1) << " "
              << product_family_info;
    std::cout << "Vendor:\t" << vendor_info;
    std::cout << "OS:\t" << os_info;
    std::cout << "CPU:\t" << cpu_info;
    std::cout << "Memory Total:\t" << mem_total_info;
    std::cout << "Memory Free:\t" << mem_free_info;

    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);

    return EXIT_SUCCESS;
}
