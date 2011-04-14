declare variable $document external;
let $matches := doc($document)/matches/match
for $match in $matches
  return
   ( $match/@teams/string(),
     $match/@score/string(),
     $match/@begin/string()
   )
