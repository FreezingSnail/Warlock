#pragma once

enum class Role {
    None,
    Fighter,
    Wizard,
    Tank,
    Theif,
};

static uint16_t ClassDie(Role role) {
    switch (role) {
    case Role::Fighter:
    case Role::Tank:
    case Role::Theif:
    case Role::Wizard:
        return 10;
    default:
        return 0;
    }
};