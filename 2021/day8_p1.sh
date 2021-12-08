#!/bin/sh
cat day8.input | cut -d ' ' -f 12- | grep -oE '\<[[:alpha:]]{2}\>|\<[[:alpha:]]{4}\>|\<[[:alpha:]]{3}\>|\<[[:alpha:]]{7}\>' |wc -l
