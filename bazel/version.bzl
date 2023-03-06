vsomeip_version = struct(
    VSOMEIP_HOTFIX_VERSION = 3,
    VSOMEIP_MAJOR_VERSION = 3,
    VSOMEIP_MINOR_VERSION = 1,
    VSOMEIP_PATCH_VERSION = 20,
)

def vsomeip_version_str():
    version = "%s.%s.%s" % (
        vsomeip_version.VSOMEIP_MAJOR_VERSION,
        vsomeip_version.VSOMEIP_MINOR_VERSION,
        vsomeip_version.VSOMEIP_PATCH_VERSION,
    )

    if vsomeip_version.VSOMEIP_HOTFIX_VERSION > 0:
        version += ".%s" % vsomeip_version.VSOMEIP_HOTFIX_VERSION

    return version
