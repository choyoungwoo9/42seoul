#include <iostream>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    int kq = kqueue();
    if (kq == -1) {
        std::cerr << "Failed to create kqueue" << std::endl;
        return 1;
    }

    struct kevent events[1];
    struct kevent event;
    EV_SET(&event, STDIN_FILENO, EVFILT_READ, EV_ADD, 0, 0, nullptr);

    if (kevent(kq, &event, 1, nullptr, 0, nullptr) == -1) {
        std::cerr << "Failed to register event" << std::endl;
        return 1;
    }

    std::cout << "Waiting for input..." << std::endl;

    while (true) {
        int nevents = kevent(kq, nullptr, 0, events, 1, nullptr);
        if (nevents == -1) {
            std::cerr << "Failed to wait for events" << std::endl;
            return 1;
        }

        if (nevents > 0) {
            if (events[0].ident == STDIN_FILENO) {
                char buffer[1024];
                ssize_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
                if (bytesRead > 0) {
                    std::cout << "Received input: " << std::string(buffer, bytesRead);
                } else if (bytesRead == -1) {
                    std::cerr << "Failed to read input" << std::endl;
                    return 1;
                } else if (bytesRead == 0) {
                    std::cout << "Input stream closed. Exiting..." << std::endl;
                    break;
                }
            }
        }
    }

    close(kq);

    return 0;
}