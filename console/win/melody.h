#pragma once
#include <windows.h>
#include <mmsystem.h>

#ifdef _WIN32
#ifndef CONSOLE_NON_MESSAGE
#pragma message("Please link with -lwinmm")
#pragma message("Use '#define CONSOLE_NON_MESSAGE' for ingore it")
#endif
#else
#error "Mismatch Operation System"
#endif

namespace console::midi
{
    namespace pitches
    {
        const int C0 = 12, D0 = 14, E0 = 16, F0 = 17, G0 = 19, A0 = 21, B0 = 23;
        const int C1 = 24, D1 = 26, E1 = 28, F1 = 29, G1 = 31, A1 = 33, B1 = 35;
        const int C2 = 36, D2 = 38, E2 = 40, F2 = 41, G2 = 43, A2 = 45, B2 = 47;
        const int C3 = 48, D3 = 50, E3 = 52, F3 = 53, G3 = 55, A3 = 57, B3 = 59;
        const int C4 = 60, D4 = 62, E4 = 64, F4 = 65, G4 = 67, A4 = 69, B4 = 71;
        const int C5 = 72, D5 = 74, E5 = 76, F5 = 77, G5 = 79, A5 = 81, B5 = 83;
        const int C6 = 84, D6 = 86, E6 = 88, F6 = 89, G6 = 91, A6 = 93, B6 = 95;
        const int C7 = 96, D7 = 98, E7 = 100, F7 = 101, G7 = 103, A7 = 105, B7 = 107;
        const int C8 = 108, D8 = 110, E8 = 112, F8 = 113, G8 = 115, A8 = 117, B8 = 119;
        const int C9 = 120, D9 = 122, E9 = 124, F9 = 125, G9 = 127;

        const int Cs0 = 13, Ds0 = 15, Fs0 = 18, Gs0 = 20, As0 = 22;
        const int Cs1 = 25, Ds1 = 27, Fs1 = 30, Gs1 = 32, As1 = 34;
        const int Cs2 = 37, Ds2 = 39, Fs2 = 42, Gs2 = 44, As2 = 46;
        const int Cs3 = 49, Ds3 = 51, Fs3 = 54, Gs3 = 56, As3 = 58;
        const int Cs4 = 61, Ds4 = 63, Fs4 = 66, Gs4 = 68, As4 = 70;
        const int Cs5 = 73, Ds5 = 75, Fs5 = 78, Gs5 = 80, As5 = 82;
        const int Cs6 = 85, Ds6 = 87, Fs6 = 90, Gs6 = 92, As6 = 94;
        const int Cs7 = 97, Ds7 = 99, Fs7 = 102, Gs7 = 104, As7 = 106;
        const int Cs8 = 109, Ds8 = 111, Fs8 = 114, Gs8 = 116, As8 = 118;
        const int Cs9 = 121, Ds9 = 123, Fs9 = 126;

        const int REST = -1;
    }

    inline int &get_bpm()
    {
        static int bpm = 120;
        return bpm;
    }

    inline void set_bpm(int bpm)
    {
        get_bpm() = bpm;
    }

    inline HMIDIOUT &get_handle()
    {
        static HMIDIOUT handle = []
        {
            HMIDIOUT h;
            if (midiOutOpen(&h, 0, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
            {
                return (HMIDIOUT) nullptr;
            }
            return h;
        }();
        return handle;
    }

    struct Note
    {
        signed char pitch;
        double beats;

        Note(int p = 60, double b = 1) : pitch((signed char)p), beats(b) {}
    };

    void play(int pitch, double beats = 1)
    {
        HMIDIOUT h = get_handle();
        if (!h)
            return;
        if (pitch != -1)
        {
            DWORD note_on = 0x90 | (pitch << 8) | (100 << 16);
            midiOutShortMsg(h, note_on);
            Sleep(60000 * beats / get_bpm());
            DWORD note_off = 0x80 | (pitch << 8) | (64 << 16);
            midiOutShortMsg(h, note_off);
        }
        else
            Sleep(60000 * beats / get_bpm());
    }

    void play(Note note)
    {
        play(note.pitch, note.beats);
    }

    template <size_t N>
    void play(const Note (&melody)[N])
    {
        for (Note note : melody)
            play(note);
    }
}
