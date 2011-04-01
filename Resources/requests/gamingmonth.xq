declare variable $document external;
element matches{
  let $matchList :=  doc($document)//*:table[starts-with(@class, "matches_table")] 
  let $days :=  $matchList//*:td[starts-with(@class, "date")]//*:h4 
  let $matches := $matchList//*:td[starts-with(@class, "team")]//*:table 
  let $countings := $matchList//*:td[starts-with(@class, "counting")]//*:table 

  for $day at $i in $days
     return
      element day {
        attribute value {$day/text()}, 
        let $mm := $matches[$i]//*:tr//*:td
        let $cc := $countings[$i]//*:tr//*:td 
        for $match at $j in $mm
          return 
              element match {
                 element teams {data($match)},
                 element count {data($cc[$j])}
              }
      }            
}
