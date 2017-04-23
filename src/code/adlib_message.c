struct music_packet {
    char reg;    // Sent to register port.
    char data;   // Sent to data port.
    int delay;   // How much to wait.
}