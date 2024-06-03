
### PLAN

The goal of the modifier system is to allow a dynamic and easily programmable interface for entity modifiers. This will generally consist of callback functions being applied to an entity or gameplay system. This is different from the main engine system because it outlines how a programmer may provide callbacks and modifiers to their own entities rather than to the core engine.

### TODO

Add actual threads and queues to the occlusion example to perform the actual callback.

Improve memory change function to do in-place allocations if possible, ie adding on to an existing region rather than moving it to a larger space