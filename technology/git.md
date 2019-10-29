Git Notes
====================

Useful git information and commands.


FAQs
------------

### How to view all commits?

    git log --oneline
    # with graph
    git log --online --graph

### How to manage git stash?

    git stash --help  # useful help
    git stash  # simply stash the changes
    git stash save "comment on this stash"  # stash the changes with comment
    git stash pop  # pop and apply the latest stash to the working directory
    git stash apply  # apply the latest stash to the working directory
    git stash list  #lists all stashes
    git stash pop stash@{1} # pop and apply stash 1

### How to delete a commit?

    git reset --hard HEAD~1  # just the last commit
    git reset --hard <sha1-commit-id>   # for any commit
    git push origin HEAD --force  # push the changes to the server

