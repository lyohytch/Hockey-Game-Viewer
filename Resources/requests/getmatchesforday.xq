declare variable $document external;
declare variable $date external;
element day{
attribute value{$date},
let $day := doc($document)//*:day[starts-with(@value, $date)]/*:match
for $match in $day
return $match
}