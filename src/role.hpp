#pragma once

enum Role {
    Fighter,
    Wizard,
    Tank,
    Theif,
};

constexpr uint16_t ClassDie(Role role) {
    switch (role) {
    case Role::Fighter:
    case Role::Tank:
    case Role::Theif:
    case Role::Wizard:
        return 10;
    default:
        return 0;
    }
}