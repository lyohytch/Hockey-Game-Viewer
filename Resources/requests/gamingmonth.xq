declare variable $document external;
element matches{
  let $days :=  doc($document)//*:td[starts-with(@class, "date")]//*:h4 
  for $day in $days
     return
      element day {
        attribute value {$day/text()}, 
        let $mm := $day/../..//*:td[starts-with(@class, "team")]//*:table//*:tr//*:td
        let $cc := $day/../..//*:td[starts-with(@class, "counting")]//*:table//*:tr//*:td
        for $match at $j in $mm
          return 
              element match {
                 element teams {data($match)},
                 element count {data($cc[$j])}
              }
      }            
}
