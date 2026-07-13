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
