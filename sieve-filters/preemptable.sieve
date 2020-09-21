require ["fileinto"];

# GitHub
if anyof (
    address :contains "from" "support@github.com",
    address :contains "from" "notifications@github.com")
{
    fileinto "GitHub";
}

# Fedora Discourse
if address :contains "from" "fedoraproject@discoursemail.com"
{
    fileinto "Fedora Discourse";
}

# froopyland
if address :contains "from" "root@preemptable.org"
{
    fileinto "froopyland";
}

# debian-security-announce
if header :contains "list-id" "debian-security-announce.lists.debian.org"
{
    fileinto "debian-security-announce";
}

# oss-security
if header :contains "list-id" "oss-security.lists.openwall.com"
{
    fileinto "oss-security";
}
