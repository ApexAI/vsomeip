# Placeholder subscription fixes

## Specific-event placeholder upgrade

When a subscription for a specific event arrives before its provider has
registered that event, the routing manager creates a cache-placeholder event
and stores the subscriber in its eventgroup.

If the provider subsequently registers the event without explicit eventgroups,
vSomeIP derives the eventgroup from the notifier ID. Previously, that upgrade
used `event::set_eventgroups`, which replaced the existing client set for that
eventgroup. Consequently, a subscription whose eventgroup equals the notifier
ID was silently removed.

The upgrade now uses `event::add_eventgroup`. It creates the implicit
eventgroup when needed while preserving subscribers already held by the
placeholder.

## ANY_EVENT placeholder transfer

The public eventgroup-subscription API defaults to `ANY_EVENT`. If such a
subscription arrived before the provider registered an event, the routing
manager stored it in an `ANY_EVENT` cache placeholder. On a later provider
registration without explicit eventgroups, the real event correctly used its
notifier ID as an implicit eventgroup, but subscriber transfer iterated the
empty eventgroup argument instead. No subscriber was copied to the real event.

Event registration now derives one effective eventgroup set before updating
the event. The same set is used for event membership, eventgroup metadata, and
transfer from an `ANY_EVENT` placeholder, so implicit eventgroups are handled
the same way as explicit ones.
