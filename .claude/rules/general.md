# Language Policy

- **Internal reasoning:** English
- **User interaction:** Japanese

> Think in English, communicate in Japanese.
>

This policy ensures consistent and natural communication for Japanese-speaking users while maintaining compatibility with English-based coding conventions, reasoning processes, and variable naming standards.

# Agent Development Principles

These are core principles every AI coding assistant or autonomous agent must follow when generating, designing, or reasoning about code.

They ensure clarity, maintainability, and reliability in all outputs.

---

## 🧩 1. DRY — Don't Repeat Yourself

> "Avoid duplication; express each idea once."
>
- Never produce redundant or repeated logic.
- When a concept or pattern appears more than once, abstract it.
- Promote code reuse through functions, modules, or utilities.

---

## 🧠 2. KISS — Keep It Simple, Stupid

> "Simplicity beats cleverness."
>
- Prefer clear, direct solutions over complex abstractions.
- Avoid overengineering or unnecessary generalization.
- Simplicity improves readability, debugging, and collaboration.

---

## 🔮 3. YAGNI — You Aren't Gonna Need It

> "Do not build for hypothetical future needs."
>
- Do not include speculative features or abstractions.
- Implement only what is necessary for the current requirements.
- Focus on present clarity over imagined flexibility.

---

## 🧱 4. SOLID Principles

> Design for flexibility, maintainability, and scalability.
>
1. **Single Responsibility** — Each component should have one clear purpose.
2. **Open/Closed** — Be open for extension, closed for modification.
3. **Liskov Substitution** — Subtypes must behave consistently with their base types.
4. **Interface Segregation** — Do not force code to depend on unused methods.
5. **Dependency Inversion** — Depend on abstractions, not on details.

---

## ⚙️ 5. SoC — Separation of Concerns

> "Divide responsibilities and respect boundaries."
>
- Keep UI, logic, and data handling distinct.
- Do not let unrelated concerns leak between layers.
- Encourage modular, testable structures.

---

## 🧭 6. Law of Demeter

> "Talk only to your friends."
>
- Avoid deep object chains and excessive coupling.
- Design interfaces that express intent without exposing internals.

---

## 🧪 7. Fail Fast Principle

> "Detect and report errors early."
>
- Prefer explicit errors over silent failures.
- Generate code that surfaces problems quickly and clearly.
- Never hide issues behind implicit behavior.

---

## 💡 8. POLA — Principle of Least Astonishment

> "Never surprise the developer."
>
- The code should behave as its structure and naming suggest.
- Maintain intuitive and consistent behavior across all outputs.
- When in doubt, prefer predictability over cleverness.

---

## 🧰 9. Convention Over Configuration

> "Follow conventions to reduce friction."
>
- Use standard naming, layout, and idioms of the language or framework.
- Minimize configuration by adhering to widely accepted norms.
- Prefer the familiar over the exotic.

---

## 🔐 10. Principle of Least Privilege

> "Only what's necessary."
>
- Generate code and configurations with minimal required access.
- Avoid suggesting unsafe or overly permissive defaults.
- Always respect the user's environment and security boundaries.

---

## 🌱 11. Boy Scout Rule

> "Always leave the code cleaner than you found it."
>
- If you touch or rewrite existing code, improve it slightly.
- Simplify, clarify, and modernize where appropriate.
- Encourage continuous refinement and technical hygiene.

---

## 🚫 12. Avoid WET — Write Everything Twice

> "Duplication is decay."
>
- Redundant code or explanations breed inconsistency.
- Strive for elegant reuse and centralized definitions.

---

## 🧭 13. Core Agent Mindset

> "Your goal is not to impress — it is to assist."
>
- Generate code that others can maintain.
- Explain your reasoning clearly when asked.
- Prioritize correctness, clarity, and safety over verbosity or novelty.

---

## ✅ Summary

| Principle | Meaning | Agent Responsibility |
| --- | --- | --- |
| **DRY** | Avoid repetition | Detect and consolidate duplication |
| **KISS** | Keep things simple | Generate straightforward, readable code |
| **YAGNI** | Don't overbuild | Focus on current needs |
| **SOLID** | Object-oriented design | Suggest maintainable structures |
| **SoC** | Separation of concerns | Respect modular boundaries |
| **Law of Demeter** | Minimal coupling | Avoid deep dependencies |
| **POLA** | Predictable behavior | Never surprise users |
| **Fail Fast** | Early error detection | Prefer explicit error handling |
| **Convention over Configuration** | Follow norms | Use community best practices |
| **Least Privilege** | Security first | Generate safe defaults |
| **Boy Scout Rule** | Continuous improvement | Always leave code cleaner |
| **Avoid WET** | Avoid duplication | Prefer reuse and abstraction |
