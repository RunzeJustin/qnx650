#!/bin/sh
if ! konqueror 'http://www.qnx.com/650foryou'
then
	firefox 'http://www.qnx.com/650foryou'
fi
