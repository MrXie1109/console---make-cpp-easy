#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <thread>

#ifdef _WIN32
#ifndef CONSOLE_IGNORE_ADVICE
#pragma message("Remember to link against winmm library (e.g., -lwinmm or winmm.lib)")
#pragma message("Define 'CONSOLE_IGNORE_ADVICE' for ignore it")
#endif
#else
#error "Unsupported platform"
#endif

namespace console
{
    enum class Instrument : unsigned char
    {
        AcousticGrandPiano = 0,   // 大钢琴 (默认)
        BrightAcousticPiano = 1,  // 明亮的钢琴
        ElectricGrandPiano = 2,   // 电子大钢琴
        HonkyTonkPiano = 3,       // 酒吧钢琴
        ElectricPiano1 = 4,       // 电钢琴 1
        ElectricPiano2 = 5,       // 电钢琴 2
        Harpsichord = 6,          // 大键琴
        Clavinet = 7,             // 击弦古钢琴
        Celesta = 8,              // 钢片琴
        Glockenspiel = 9,         // 钟琴
        MusicBox = 10,            // 八音盒
        Vibraphone = 11,          // 颤音琴
        Marimba = 12,             // 马林巴
        Xylophone = 13,           // 木琴
        TubularBells = 14,        // 管钟
        Dulcimer = 15,            // 扬琴
        DrawbarOrgan = 16,        // 拉杆风琴
        PercussiveOrgan = 17,     // 打击型风琴
        RockOrgan = 18,           // 摇滚风琴
        ChurchOrgan = 19,         // 教堂风琴
        ReedOrgan = 20,           // 簧风琴
        Accordion = 21,           // 手风琴
        Harmonica = 22,           // 口琴
        TangoAccordion = 23,      // 探戈手风琴
        AcousticGuitarNylon = 24, // 尼龙弦吉他
        AcousticGuitarSteel = 25, // 钢弦吉他
        ElectricGuitarJazz = 26,  // 爵士吉他
        ElectricGuitarClean = 27, // 清音电吉他
        ElectricGuitarMuted = 28, // 闷音吉他
        OverdrivenGuitar = 29,    // 过载吉他
        DistortionGuitar = 30,    // 失真吉他
        GuitarHarmonics = 31,     // 吉他泛音
        AcousticBass = 32,        // 原声贝司
        ElectricBassFinger = 33,  // 指拨电贝司
        ElectricBassPick = 34,    // 拨片电贝司
        FretlessBass = 35,        // 无品贝司
        SlapBass1 = 36,           // 击弦贝司 1
        SlapBass2 = 37,           // 击弦贝司 2
        SynthBass1 = 38,          // 合成贝司 1
        SynthBass2 = 39,          // 合成贝司 2
        Violin = 40,              // 小提琴
        Viola = 41,               // 中提琴
        Cello = 42,               // 大提琴
        Contrabass = 43,          // 低音提琴
        TremoloStrings = 44,      // 弦乐颤音
        PizzicatoStrings = 45,    // 弦乐拨奏
        OrchestralHarp = 46,      // 竖琴
        Timpani = 47,             // 定音鼓
        StringEnsemble1 = 48,     // 弦乐合奏 1
        StringEnsemble2 = 49,     // 弦乐合奏 2
        SynthStrings1 = 50,       // 合成弦乐 1
        SynthStrings2 = 51,       // 合成弦乐 2
        ChoirAahs = 52,           // 合唱 "啊"
        VoiceOohs = 53,           // 人声 "哦"
        SynthVoice = 54,          // 合成人声
        OrchestraHit = 55,        // 乐队打击乐
        Trumpet = 56,             // 小号
        Trombone = 57,            // 长号
        Tuba = 58,                // 大号
        MutedTrumpet = 59,        // 弱音小号
        FrenchHorn = 60,          // 圆号
        BrassSection = 61,        // 铜管组
        SynthBrass1 = 62,         // 合成铜管 1
        SynthBrass2 = 63,         // 合成铜管 2
        SopranoSax = 64,          // 高音萨克斯
        AltoSax = 65,             // 中音萨克斯
        TenorSax = 66,            // 次中音萨克斯
        BaritoneSax = 67,         // 上低音萨克斯
        Oboe = 68,                // 双簧管
        EnglishHorn = 69,         // 英国管
        Bassoon = 70,             // 巴松管
        Clarinet = 71,            // 单簧管
        Piccolo = 72,             // 短笛
        Flute = 73,               // 长笛
        Recorder = 74,            // 竖笛
        PanFlute = 75,            // 排箫
        BlownBottle = 76,         // 吹瓶口
        Shakuhachi = 77,          // 尺八
        Whistle = 78,             // 口哨
        Ocarina = 79,             // 奥卡雷纳
        Lead1Square = 80,         // 方波领奏
        Lead2Sawtooth = 81,       // 锯齿波领奏
        Lead3Calliope = 82,       // 汽笛风琴
        Lead4Chiff = 83,          // 气声领奏
        Lead5Charang = 84,        // 炭精吉他
        Lead6Voice = 85,          // 人声领奏
        Lead7Fifths = 86,         // 五度领奏
        Lead8BassLead = 87,       // 贝司领奏
        Pad1NewAge = 88,          // 新世纪背景
        Pad2Warm = 89,            // 温暖背景
        Pad3Polysynth = 90,       // 复音合成背景
        Pad4Choir = 91,           // 合唱背景
        Pad5Bowed = 92,           // 弓弦背景
        Pad6Metallic = 93,        // 金属背景
        Pad7Halo = 94,            // 光环背景
        Pad8Sweep = 95,           // 扫弦背景
        Fx1Rain = 96,             // 雨声
        Fx2Soundtrack = 97,       // 电影配乐
        Fx3Crystal = 98,          // 水晶
        Fx4Atmosphere = 99,       // 大气
        Fx5Brightness = 100,      // 明亮
        Fx6Goblins = 101,         // 小妖
        Fx7Echoes = 102,          // 回声
        Fx8SciFi = 103,           // 科幻
        Sitar = 104,              // 西塔琴
        Banjo = 105,              // 班卓琴
        Shamisen = 106,           // 三味线
        Koto = 107,               // 古筝
        Kalimba = 108,            // 卡林巴
        Bagpipe = 109,            // 风笛
        Fiddle = 110,             // 民间提琴
        Shanai = 111,             // 唢呐
        TinkleBell = 112,         // 铃铛
        Agogo = 113,              // 阿果果铃
        SteelDrums = 114,         // 钢鼓
        Woodblock = 115,          // 木鱼
        TaikoDrum = 116,          // 太鼓
        MelodicTom = 117,         // 旋律通鼓
        SynthDrum = 118,          // 合成鼓
        ReverseCymbal = 119,      // 反奏钹
        GuitarFretNoise = 120,    // 吉他擦弦声
        BreathNoise = 121,        // 呼吸声
        Seashore = 122,           // 海浪
        BirdTweet = 123,          // 鸟鸣
        TelephoneRing = 124,      // 电话铃
        Helicopter = 125,         // 直升机
        Applause = 126,           // 掌声
        Gunshot = 127             // 枪声
    };

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

    struct Note
    {
        signed char pitch;
        double beats;
        signed char volume;

        Note(signed char p = 60, double b = 1, signed char v = -1)
            : pitch(p), beats(b), volume(v) {}
    };

    class MIDI
    {
        HMIDIOUT handle;
        unsigned char bpm;
        unsigned char volume;
        Instrument instrument;

    public:
        MIDI(Instrument instrument = Instrument::AcousticGrandPiano,
             unsigned char bpm = 120,
             unsigned char volume = 100,
             unsigned deviceID = 0)
            : bpm(bpm), volume(volume), instrument(instrument)
        {
            HMIDIOUT h = nullptr;
            if (midiOutOpen(&h, deviceID, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR)
            {
                handle = h;
                DWORD program_change = 0xC0 | ((unsigned char)(instrument) << 8);
                midiOutShortMsg(handle, program_change);
                DWORD volume_change = 0xB0 | (0x07 << 8) | (volume << 16);
                midiOutShortMsg(handle, volume_change);
            }
            else
                handle = nullptr;
        }
        MIDI(const MIDI &) = delete;
        MIDI(MIDI &&midi) = delete;
        const MIDI &operator=(const MIDI &) = delete;
        const MIDI &operator=(MIDI &&) = delete;
        ~MIDI() noexcept
        {
            if (handle)
                midiOutClose(handle);
        }

        unsigned char get_bpm() const { return bpm; }
        void set_bpm(unsigned char new_bpm) { bpm = new_bpm; }

        Instrument get_instrument() { return instrument; }
        void set_instrument(Instrument new_instrument)
        {
            instrument = new_instrument;
            if (!handle)
                return;
            DWORD program_change = 0xC0 | ((unsigned char)(new_instrument) << 8);
            midiOutShortMsg(handle, program_change);
        }

        unsigned char get_volume() const { return volume; }
        void set_volume(unsigned char vol)
        {
            volume = vol;
            if (!handle)
                return;
            DWORD volume_change = 0xB0 | (0x07 << 8) | (vol << 16);
            midiOutShortMsg(handle, volume_change);
        }

        void play(Note note)
        {
            if (!handle)
                return;
            if (note.pitch != -1)
            {
                DWORD note_on = 0x90 | (note.pitch << 8) |
                                ((note.volume == -1
                                      ? volume
                                      : note.volume)
                                 << 16);
                midiOutShortMsg(handle, note_on);
                Sleep(60000 * note.beats / bpm);
                DWORD note_off = 0x80 | (note.pitch << 8) | (64 << 16);
                midiOutShortMsg(handle, note_off);
            }
            else
                Sleep(60000 * note.beats / bpm);
        }

        void nplay(Note note)
        {
            std::thread([this, note]()
                        { play(note); })
                .detach();
        }

        template <size_t N>
        void play(const Note (&notes)[N])
        {
            for (Note note : notes)
                play(note);
        }

        template <size_t N>
        void nplay(const Note (&notes)[N])
        {
            std::thread([this, &notes]()
                        { play(notes); })
                .detach();
        }
    };
}
