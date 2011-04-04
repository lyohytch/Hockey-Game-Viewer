declare variable $document external;
declare variable $date external;
let $day := doc($document)//*:day[starts-with(@value, $date)]/*:match
for $match in $day
return $match/count/string()
