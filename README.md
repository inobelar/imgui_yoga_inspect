# ImGui Yoga inspection utils

Tiny library for Yoga's layout visualization & inspection nodes properties with
Dear ImGui.

## Dependencies

- [Dear ImGui](https://github.com/ocornut/imgui)
- [Yoga](https://github.com/facebook/yoga)

## FAQ

- Question: Why it named so - "inspection", not "reflection" or even "introspection" ?
- Answer:
    - Accordingly to [Wikipedia :: Type introspection](https://en.wikipedia.org/wiki/Type_introspection)

        > **Introspection** should not be confused with
        **[reflection](https://en.wikipedia.org/wiki/Reflective_programming)**,
        which goes a step further and is the ability for a program to manipulate
        the values, metadata, properties, and functions of an object at runtime.

    - Accordingly to [LinkedIn :: StanleyRedwood :: The Philosophy of Psychology: INTROSPECTION](https://www.linkedin.com/pulse/introspection-stanley-redwood#:~:text=An%20inspection%20is%20a%20careful,and%20specere%20(to%20look).)

        > An **inspection** is a careful and thorough examination. It is often
        intrusive and sometimes uncomfortable. **Introspection** is the same,
        only inward looking. Introspection derives from the Latin words
        **intro** (inside) and **specere** (to look).

    The **main goal** of this library is to provide 'inspection' ability
    (for embedding into other projects with, typically, custom nodes handling).

    We also provide 'reflection' ability (to modify nodes), but typically its
    suitable only for educational purpose - to see how changing nodes properties
    affects layout.

    Since we uses public C API for it, and not dig into private data, it's
    definetely 'inspection', not 'introspection'.

