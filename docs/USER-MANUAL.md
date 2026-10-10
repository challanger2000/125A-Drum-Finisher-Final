# 125A Drum Finisher V1.0.0 — User Manual

## Purpose

A stereo drum-bus effect providing five independent processing dimensions and selectable character voicings. Designed for full stereo drum busses rather than MIDI generation.

## Signal controls

- **PUNCH** — shapes drum transient impact and perceived attack.
- **MASS** — adjusts drum weight and low-frequency body.
- **TIGHT** — controls envelope and perceived tightness.
- **FINISH** — adaptive reduction of problematic ringing/resonance; on nonresonant sources, its audible action may be subtle by design.
- **GLUE** — stereo-linked bus compression for cohesion.
- **OUTPUT** — output gain, nominal range ±12 dB, default 0 dB.

Each effect amount is displayed as a percentage; 0% is neutral for that module. The percent scale describes effect amount, not frequency or level in dB.

## CHARACTER

Choose **PUNCH**, **TIGHT**, or **DENSE** using the three buttons. These are distinct processing voicings, not extra independent effect slots; their sound depends on incoming drum material and active amounts.

## BYPASS

One BYPASS button switches between processed and bypassed signal. Use level-matched listening when evaluating changes: increased loudness alone is not proof of improved sound.

## Zoom and control operation

Use the editor's 100%/150% zoom control for display scaling. Value readouts below the controls display % or dB as applicable. CTRL + left-click requests the defined default reset.

## Suggested workflow

Start at neutral amounts, then raise a single module to hear its distinct contribution. Try 20–50% for musically useful adjustments; stronger ranges are available for more conspicuous processing. Compare CHARACTER modes on the same input and avoid compensating for level differences with a subjective loudness judgment. Use OUTPUT to match the dry/wet audition level.

## Host/session integration

The plugin is a stereo-in/stereo-out audio effect, not a MIDI instrument. Parameter automation and VST3 state save/restore are covered by automated QA; your host manages project persistence. Report any DAW-specific interaction defect along with host version and reproduction steps.

## Technical information

Windows x64 VST3, 32-bit and 64-bit floating-point audio paths; zero plugin-reported latency and a conservative one-second reported tail. Exact tested binary: QA #14, build commit `8ab575977aa6dfdd04614c957db5f4fd7bd8e6ed`.
